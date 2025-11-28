-- deduct_stock.lua
local key = KEYS[1]
local amount = tonumber(ARGV[1])

-- 1. 獲取當前庫存 (注意: redis.call 回傳的是 string，要轉 number)
local current = tonumber(redis.call('GET', key))

-- 2. 判斷邏輯
if current == nil then
    return -1 -- 錯誤：商品不存在
end

if current < amount then
    return 0 -- 失敗：庫存不足
else
    redis.call('DECRBY', key, amount)
    return 1 -- 成功：扣減成功
end