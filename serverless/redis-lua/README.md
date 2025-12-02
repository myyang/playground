# Redis Lua Scripts

Collection of Redis Lua scripts for common distributed system patterns.

## Scripts

| Script | Description |
|--------|-------------|
| `rate_limit_token.lua` | Token Bucket rate limiting algorithm |
| `rate_limit_leaky.lua` | Leaky Bucket rate limiting algorithm |
| `distributed_lock_utils.lua` | Distributed lock with fencing token support (ACQUIRE/RELEASE/RENEW) |
| `atomic_check_and_modify.lua` | Atomic check-and-modify operations |
| `atomic_get_and_set.lua` | Atomic get-and-set operations |

## Rate Limiting

### Token Bucket

Allows burst traffic while maintaining average rate.

```bash
EVAL "$(cat rate_limit_token.lua)" 1 "ratelimit:api:user123" 100 10 1
# Args: key, capacity, refill_rate, tokens_to_consume
# Returns: {allowed, remaining_tokens}
```

## Distributed Lock

Supports:
- Re-entrancy (same owner can re-acquire)
- Fencing tokens (prevent stale writes)
- Lock renewal (watchdog pattern)

```bash
# Acquire
EVAL "$(cat acquire.lua)" 1 "lock:task:123" "worker-abc" 30000

# Release
EVAL "$(cat release.lua)" 1 "lock:task:123" "worker-abc"

# Renew
EVAL "$(cat renew.lua)" 1 "lock:task:123" "worker-abc" 30000
```

## When to Use Distributed Lock

| Good Use Cases | Bad Use Cases (Use Alternatives) |
|----------------|----------------------------------|
| Scheduled task singleton | Same Redis data ops (use Lua) |
| Leader election | DB transactions (use SELECT FOR UPDATE) |
| External API rate limit | Optimistic lock fits (use version field) |
| Cross-service coordination | Strong consistency (use ZooKeeper/etcd) |
