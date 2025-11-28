-- =============================================================================
-- distributed_lock_utils.lua
-- Redis Distributed Lock Utilities with Fencing Token Support (v2)
-- =============================================================================
--
-- OVERVIEW:
--   This file contains three lock operations: ACQUIRE, RELEASE, RENEW
--   Each operation is designed to be used independently via EVALSHA
--
-- VERSION 2 IMPROVEMENTS:
--   1. Re-entrancy support (same owner can re-acquire without failure)
--   2. Long-lived fence key (24h TTL) prevents token reset during long tasks
--   3. RENEW extends both lock and fence key TTL
--   4. RELEASE does not delete fence key (maintains monotonicity)
--
-- =============================================================================
-- WHEN TO USE DISTRIBUTED LOCK
-- =============================================================================
--
-- GOOD USE CASES:
-- +-----------------------------+------------------------------------------------+
-- | Scenario                    | Description                                    |
-- +-----------------------------+------------------------------------------------+
-- | Scheduled Task Singleton    | Multiple cron instances, only one should run   |
-- | Leader Election             | Elect a leader to coordinate workers           |
-- | External API Rate Limit     | Third-party API has concurrency restrictions   |
-- | Duplicate Processing Guard  | Auxiliary protection for message queue         |
-- | Cross-Service Coordination  | Multiple services operate same external system |
-- +-----------------------------+------------------------------------------------+
--
-- BAD USE CASES (USE ALTERNATIVES INSTEAD):
-- +-----------------------------+------------------------------------------------+
-- | Scenario                    | Better Alternative                             |
-- +-----------------------------+------------------------------------------------+
-- | Same Redis Data Operations  | Lua Script atomic operations                   |
-- | DB Transaction Scenarios    | SELECT FOR UPDATE, DB Transaction              |
-- | Optimistic Lock Fits        | Version field + CAS pattern                    |
-- | Strong Consistency Required | ZooKeeper, etcd (Raft/Paxos consensus)         |
-- +-----------------------------+------------------------------------------------+
--
-- =============================================================================
-- DECISION FLOWCHART:
-- =============================================================================
--
--   Need concurrency control?
--          |
--          v
--   +-------------------------+
--   | All data in same Redis? |
--   +-------------------------+
--       | Yes           | No
--       v               v
--   Lua Script    +-----------------+
--                 | Data in DB?     |
--                 +-----------------+
--                    | Yes       | No
--                    v           v
--              DB Transaction   Distributed Lock
--              + Optimistic     + Fencing Token
--                Lock
--
-- =============================================================================
-- IMPORTANT NOTES:
-- =============================================================================
--
-- 1. Fencing Token: Each successful ACQUIRE returns an incrementing token.
--    Pass this token to your storage layer to prevent stale operations.
--    Example: UPDATE t SET data='x', fence=42 WHERE id=1 AND fence < 42
--
-- 2. Lock Expiry Risk: If your operation takes longer than TTL, another
--    client may acquire the lock. Use RENEW or rely on fencing tokens.
--
-- 3. Re-entrancy: Same owner can call ACQUIRE multiple times safely.
--    It will refresh TTL and return the existing fence token.
--
-- 4. Fence Key Lifecycle: Fence key has 24h TTL, extended on each RENEW.
--    Never deleted on RELEASE to maintain monotonic increment property.
--
-- =============================================================================


-- =============================================================================
-- [ACTION 1] ACQUIRE LOCK (v2)
-- =============================================================================
-- Attempts to acquire a distributed lock with fencing token support
-- Supports re-entrancy: same owner can re-acquire to refresh TTL
--
-- KEYS[1] = lock key (e.g., "lock:order:12345")
-- ARGV[1] = owner_id (unique identifier, e.g., "worker-1:uuid")
-- ARGV[2] = ttl_ms (lock expiration in milliseconds, e.g., 30000)
--
-- RETURNS:
--   Success: fencing_token (positive integer, incrementing)
--   Re-entry: existing fencing_token (same owner already holds lock)
--   Failure: 0 (lock is held by another owner)
--
-- USAGE EXAMPLE (redis-cli):
--   EVALSHA <sha> 1 "lock:task:123" "worker-abc" 30000
--
-- FENCING TOKEN USAGE:
--   When updating external storage, include the fencing token:
--   UPDATE table SET data='x', fence_token=42 WHERE id=1 AND fence_token < 42
--
-- RE-ENTRANCY EXAMPLE:
--   First call:  ACQUIRE "lock:x" "worker-1" 30000 -> returns 5 (new token)
--   Second call: ACQUIRE "lock:x" "worker-1" 30000 -> returns 5 (same token, TTL refreshed)
--   Other owner: ACQUIRE "lock:x" "worker-2" 30000 -> returns 0 (rejected)
-- -----------------------------------------------------------------------------
--[[ACQUIRE
local lock_key = KEYS[1]
local fence_key = lock_key .. ':fence'
local owner_id = ARGV[1]
local ttl_ms = tonumber(ARGV[2])

-- Re-entrancy Check: Do I already own this lock?
local current_owner = redis.call('GET', lock_key)
if current_owner == owner_id then
    -- Refresh TTL for both keys
    redis.call('PEXPIRE', lock_key, ttl_ms)
    redis.call('PEXPIRE', fence_key, 86400000) -- 24 hours
    -- Return existing fence token
    return tonumber(redis.call('GET', fence_key)) or 0
end

-- Try to acquire lock (NX = only if not exists)
local acquired = redis.call('SET', lock_key, owner_id, 'NX', 'PX', ttl_ms)

if acquired then
    -- Increment fence token (creates key if not exists)
    local token = redis.call('INCR', fence_key)
    -- Fence key lives much longer than lock to prevent token reset
    -- Even if lock expires and new owner acquires, token keeps incrementing
    redis.call('PEXPIRE', fence_key, 86400000) -- 24 hours
    return token
else
    return 0
end
ACQUIRE--]]


-- =============================================================================
-- [ACTION 2] RELEASE LOCK (v2)
-- =============================================================================
-- Releases a lock only if the caller is the current owner
-- IMPORTANT: Does NOT delete fence_key to maintain monotonic token increment
--
-- KEYS[1] = lock key (e.g., "lock:order:12345")
-- ARGV[1] = owner_id (must match the owner who acquired the lock)
--
-- RETURNS:
--   1 = successfully released
--   0 = not released (not owner or lock doesn't exist)
--
-- USAGE EXAMPLE (redis-cli):
--   EVALSHA <sha> 1 "lock:task:123" "worker-abc"
--
-- WHY WE DON'T DELETE FENCE KEY:
--   Fence key must persist to ensure token monotonicity.
--   If we delete it, next ACQUIRE would reset token to 1.
--   This breaks fencing protection against stale writes.
--
--   Example of what could go wrong if we deleted fence_key:
--     Worker A: ACQUIRE -> token=100, starts long DB operation
--     Worker A: RELEASE -> deletes fence_key (BAD!)
--     Worker B: ACQUIRE -> token=1 (reset!)
--     Worker A: DB write with token=100 succeeds (should have been rejected!)
--     Worker B: DB write with token=1 fails (fence < 100)
--     -> Data inconsistency!
-- -----------------------------------------------------------------------------
--[[RELEASE
local lock_key = KEYS[1]
local owner_id = ARGV[1]

local current_owner = redis.call('GET', lock_key)

if current_owner == owner_id then
    redis.call('DEL', lock_key)
    -- Do NOT delete fence_key - it must persist for monotonicity
    -- Let it expire naturally via PEXPIRE set in ACQUIRE/RENEW
    return 1
else
    return 0
end
RELEASE--]]


-- =============================================================================
-- [ACTION 3] RENEW LOCK (v2)
-- =============================================================================
-- Extends the lock TTL if the caller is still the owner
-- Also extends fence_key TTL to prevent expiration during long tasks
--
-- KEYS[1] = lock key (e.g., "lock:order:12345")
-- ARGV[1] = owner_id (must match the owner who acquired the lock)
-- ARGV[2] = ttl_ms (new expiration time in milliseconds)
--
-- RETURNS:
--   1 = successfully renewed
--   0 = not renewed (not owner or lock doesn't exist)
--
-- USAGE EXAMPLE (redis-cli):
--   EVALSHA <sha> 1 "lock:task:123" "worker-abc" 30000
--
-- WATCHDOG PATTERN:
--   1. Start background goroutine/thread that calls RENEW every ttl/3
--   2. If main task completes -> stop watchdog -> call RELEASE
--   3. If main task crashes -> watchdog stops -> lock expires naturally
--
-- WHY WE EXTEND FENCE KEY TTL:
--   Long-running tasks may exceed the original fence_key TTL.
--   If fence_key expires mid-task, next INCR creates a new key starting at 1.
--   This breaks fencing protection. Extending TTL on each RENEW prevents this.
-- -----------------------------------------------------------------------------
--[[RENEW
local lock_key = KEYS[1]
local fence_key = lock_key .. ':fence'
local owner_id = ARGV[1]
local ttl_ms = tonumber(ARGV[2])

local current_owner = redis.call('GET', lock_key)

if current_owner == owner_id then
    redis.call('PEXPIRE', lock_key, ttl_ms)
    -- Extend fence key TTL too (prevents expiration during long tasks)
    redis.call('PEXPIRE', fence_key, 86400000) -- 24 hours
    return 1
else
    return 0
end
RENEW--]]


-- =============================================================================
-- HOW TO USE THESE SCRIPTS
-- =============================================================================
--
-- Since each Redis EVAL call runs one script, extract the section you need:
--
-- 1. Copy content between --[[ACQUIRE ... ACQUIRE--]] for acquire script
-- 2. Copy content between --[[RELEASE ... RELEASE--]] for release script
-- 3. Copy content between --[[RENEW   ... RENEW--]]   for renew script
--
-- Or load this entire file and use pattern matching to extract sections
-- programmatically in your application code.
--
-- =============================================================================
-- COMPLETE WORKFLOW EXAMPLE
-- =============================================================================
--
-- func processTask(taskId string) error {
--     lockKey := "lock:task:" + taskId
--     ownerId := hostname + ":" + uuid.New()
--     ttlMs := 30000
--
--     // 1. Acquire lock (supports re-entrancy)
--     token := redis.Eval(ACQUIRE_SCRIPT, lockKey, ownerId, ttlMs)
--     if token == 0 {
--         return errors.New("failed to acquire lock")
--     }
--
--     // 2. Start watchdog (renew every 10s, extends both lock and fence)
--     stopWatchdog := startWatchdog(lockKey, ownerId, ttlMs)
--     defer stopWatchdog()
--
--     // 3. Do actual work (use fencing token for external storage)
--     err := updateDatabase(taskId, token)  // token used as fence
--     // SQL: UPDATE tasks SET status='done', fence=? WHERE id=? AND fence < ?
--
--     // 4. Release lock (fence_key persists for monotonicity)
--     redis.Eval(RELEASE_SCRIPT, lockKey, ownerId)
--
--     return err
-- }
--
-- =============================================================================
-- FENCE TOKEN PERSISTENCE TIMELINE
-- =============================================================================
--
-- Time     Event                           lock_key    fence_key (token)
-- ----     -----                           --------    -----------------
-- T+0      Worker A: ACQUIRE               A (30s)     1 (24h)
-- T+10     Worker A: RENEW                 A (30s)     1 (24h extended)
-- T+20     Worker A: RELEASE               (deleted)   1 (still exists!)
-- T+25     Worker B: ACQUIRE               B (30s)     2 (incremented!)
-- T+30     Worker A: stale write fence=1   REJECTED by DB (fence < 2)
--
-- =============================================================================
