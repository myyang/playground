-- =============================================================================
-- rate_limit_token.lua
-- Token Bucket Algorithm with Redis TIME for accurate rate limiting
-- =============================================================================
--
-- ALGORITHM:
--   Tokens are added at a constant rate (refill), consumed per request.
--   Allows burst traffic as long as bucket has enough tokens.
--
--   +------------------+
--   | Tokens refill at |-----> [Token Bucket] <----- Requests consume tokens
--   | constant rate    |       (max: capacity)
--   +------------------+
--
-- KEYS[1]: Rate Limit Key (e.g., "ratelimit:token:user:123")
-- ARGV[1]: Bucket capacity (max tokens), e.g., 100
-- ARGV[2]: Refill rate (tokens per second), e.g., 10
-- ARGV[3]: Tokens to consume (optional, default 1)
--
-- RETURNS: {allowed, remaining_tokens}
--   allowed = 1: request permitted
--   allowed = 0: request rejected (not enough tokens)
--   remaining_tokens: current token count after operation
--
-- USAGE EXAMPLE (redis-cli):
--   EVAL "$(cat rate_limit_token.lua)" 1 "ratelimit:api:user123" 100 10 1
--
-- USAGE IN CODE:
--   result = redis.eval(script, 1, "ratelimit:api:user123", 100, 10, 1)
--   if result[1] == 1 then
--       -- allowed, remaining = result[2]
--   else
--       -- rejected, can show "X-RateLimit-Remaining: result[2]"
--   end
--
-- =============================================================================

local key = KEYS[1]
local capacity = tonumber(ARGV[1])
local rate = tonumber(ARGV[2])
local requested = tonumber(ARGV[3]) or 1

-- Use Redis server time for accuracy (prevents client clock drift)
-- TIME returns {seconds, microseconds}
local time_info = redis.call('TIME')
local now = tonumber(time_info[1]) + (tonumber(time_info[2]) / 1000000)

-- Get current bucket state
local info = redis.call('HMGET', key, 'tokens', 'last_refilled')
local last_tokens = tonumber(info[1])
local last_refilled = tonumber(info[2])

-- Initialize bucket on first access (start with full capacity)
if last_tokens == nil then
    last_tokens = capacity
    last_refilled = now
end

-- Calculate tokens to refill since last access
-- Formula: (now - last_time) * rate
local delta = math.max(0, now - last_refilled)
local filled_tokens = delta * rate

-- Current tokens cannot exceed capacity
local current_tokens = math.min(capacity, last_tokens + filled_tokens)

-- Try to consume tokens
local allowed = 0
if current_tokens >= requested then
    current_tokens = current_tokens - requested
    allowed = 1
    -- Only update timestamp on success (let tokens accumulate on rejection)
    redis.call('HMSET', key, 'tokens', current_tokens, 'last_refilled', now)
    -- Set expiry to prevent stale keys (time to fill bucket * 2)
    redis.call('EXPIRE', key, math.ceil(capacity / rate * 2))
else
    -- On rejection: do NOT update last_refilled
    -- This allows tokens to continue accumulating for next request
    allowed = 0
end

return {allowed, current_tokens}
