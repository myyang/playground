-- claim_task.lua
local key = KEYS[1]
local my_id = ARGV[1]

-- 讀取當前擁有者
local current_owner = redis.call('GET', key)

-- 邏輯判斷
if current_owner == "UNASSIGNED" then
    -- 原子性寫入
    redis.call('SET', key, my_id)
    return "SUCCESS: Claimed by " .. my_id
else
    return "FAIL: Already owned by " .. current_owner
end