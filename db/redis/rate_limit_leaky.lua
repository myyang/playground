-- =============================================================================
-- rate_limit_leaky.lua
-- Leaky Bucket using GCRA (Generic Cell Rate Algorithm) for smooth rate limiting
-- =============================================================================
--
-- ALGORITHM:
--   GCRA tracks TAT (Theoretical Arrival Time) - when the next request is allowed.
--   More memory-efficient than traditional water-level tracking (1 key vs 2 fields).
--
--   Request --> [Is TAT in the past?] --> Yes: Allow, update TAT
--                      |
--                      No: Reject, return Retry-After
--
-- KEYS[1]: Rate Limit Key (e.g., "ratelimit:leaky:user:123")
-- ARGV[1]: Rate (requests per second), e.g., 10
-- ARGV[2]: Burst capacity (optional, default 1). 
--          0 = strict interval, higher = allow short bursts
--
-- RETURNS: {allowed, retry_after_ms}
--   allowed = 1: request permitted, retry_after_ms = 0
--   allowed = 0: request rejected, retry_after_ms = wait time in milliseconds
--
-- USAGE EXAMPLE (redis-cli):
--   EVAL "$(cat rate_limit_leaky.lua)" 1 "ratelimit:api:user123" 10 1
--
-- USAGE IN CODE (with Retry-After header):
--   result = redis.eval(script, 1, "ratelimit:api:user123", 10, 1)
--   if result[1] == 1 then
--       -- allowed
--   else
--       -- rejected
--       response.header("Retry-After", result[2] / 1000)  -- convert to seconds
--   end
--
-- MEMORY COMPARISON:
--   Traditional Leaky Bucket: Hash with 2 fields (~100+ bytes)
--   GCRA: Single String key (~50 bytes) = ~50% memory savings
--
-- =============================================================================

local key = KEYS[1]
local rate = tonumber(ARGV[1])
local burst = tonumber(ARGV[2]) or 1

-- Calculate emission interval in microseconds
-- rate = 10 req/s -> interval = 100,000 μs (0.1s between requests)
local emission_interval = 1000000 / rate

-- Get current time from Redis (microsecond precision)
-- TIME returns {seconds, microseconds}
local time_info = redis.call('TIME')
local now = tonumber(time_info[1]) * 1000000 + tonumber(time_info[2])

-- Get last TAT (Theoretical Arrival Time)
-- If key doesn't exist, TAT = now (bucket is empty, ready for request)
local tat = tonumber(redis.call('GET', key)) or now

-- Calculate new TAT
-- If TAT < now: bucket was empty, start fresh from now
-- If TAT > now: requests are queued, add to existing TAT
local new_tat = math.max(tat, now) + emission_interval

-- Calculate the maximum allowed TAT (how far ahead we can queue)
-- burst = 0: strict, only allow if TAT <= now + interval
-- burst = N: allow N requests worth of queue ahead
local allow_at = now + emission_interval + (burst * emission_interval)

if new_tat <= allow_at then
    -- Request allowed
    -- Update TAT and set expiry (prevent stale keys)
    local expiry_seconds = math.ceil((burst + 2) * emission_interval / 1000000)
    redis.call('SET', key, new_tat, 'EX', expiry_seconds)
    return {1, 0}
else
    -- Request rejected
    -- Calculate how long client should wait before retrying
    local wait_time_ms = math.ceil((new_tat - allow_at) / 1000)
    return {0, wait_time_ms}
end
