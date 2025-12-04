-- PostgreSQL Partitioning Practice

-- ==========================================
-- 1. Declarative Partitioning: Range
-- ==========================================

-- Step 1: Create the parent table
CREATE TABLE orders_range (
    order_id SERIAL,
    order_date DATE NOT NULL,
    amount DECIMAL(10, 2)
) PARTITION BY RANGE (order_date);

-- Step 2: Create partitions
CREATE TABLE orders_2020 PARTITION OF orders_range
    FOR VALUES FROM ('2020-01-01') TO ('2021-01-01');

CREATE TABLE orders_2021 PARTITION OF orders_range
    FOR VALUES FROM ('2021-01-01') TO ('2022-01-01');

CREATE TABLE orders_default PARTITION OF orders_range DEFAULT;


-- ==========================================
-- 2. Declarative Partitioning: List
-- ==========================================

-- Step 1: Create the parent table
CREATE TABLE users_list (
    user_id INT NOT NULL,
    country_code CHAR(2) NOT NULL
) PARTITION BY LIST (country_code);

-- Step 2: Create partitions
CREATE TABLE users_us PARTITION OF users_list
    FOR VALUES IN ('US');

CREATE TABLE users_eu PARTITION OF users_list
    FOR VALUES IN ('DE', 'FR', 'IT', 'ES');

-- [NOTE] Default Partition
-- Postgres supports a DEFAULT partition for values not matching any other partition.
-- This prevents insert errors but makes adding future specific partitions harder
-- (you must check if the new value exists in default first).
CREATE TABLE users_default PARTITION OF users_list DEFAULT;


-- ==========================================
-- 3. Declarative Partitioning: Hash
-- Useful for distributing data evenly (e.g., sharding-like behavior).
-- [WARNING] Resharding (changing partition count) in Postgres Hash Partitioning is HARD.
-- You cannot simply "add" a partition. You typically must migrate data to a new table
-- with a different modulus. Choose your modulus wisely upfront!
-- ==========================================

-- Step 1: Create the parent table
CREATE TABLE cache_hash (
    key_id INT NOT NULL,
    value TEXT
) PARTITION BY HASH (key_id);

-- Step 2: Create partitions (Modulus must match the number of partitions)
CREATE TABLE cache_p0 PARTITION OF cache_hash
    FOR VALUES WITH (MODULUS 4, REMAINDER 0);

CREATE TABLE cache_p1 PARTITION OF cache_hash
    FOR VALUES WITH (MODULUS 4, REMAINDER 1);

CREATE TABLE cache_p2 PARTITION OF cache_hash
    FOR VALUES WITH (MODULUS 4, REMAINDER 2);

CREATE TABLE cache_p3 PARTITION OF cache_hash
    FOR VALUES WITH (MODULUS 4, REMAINDER 3);


-- ==========================================
-- 4. Multi-level Partitioning (Sub-partitioning)
-- Concept: Partition a table that is already a partition of another table.
-- Use case: Range by Date (for retention) + Hash by ID (for load balancing).
-- ==========================================

-- Step 1: Grandparent (Level 1: Range)
CREATE TABLE logs_composite (
    log_id INT,
    log_ts DATE,
    user_id INT,
    msg TEXT
) PARTITION BY RANGE (log_ts);

-- Step 2: Parent (Level 2: This partition IS A TABLE that is partitioned by Hash)
-- We define a partition for 2023, but instead of storage, we say it's partitioned by HASH.
CREATE TABLE logs_2023 PARTITION OF logs_composite
    FOR VALUES FROM ('2023-01-01') TO ('2024-01-01')
    PARTITION BY HASH (user_id);

-- Step 3: Children (Level 3: Actual storage)
CREATE TABLE logs_2023_p0 PARTITION OF logs_2023 FOR VALUES WITH (MODULUS 4, REMAINDER 0);
CREATE TABLE logs_2023_p1 PARTITION OF logs_2023 FOR VALUES WITH (MODULUS 4, REMAINDER 1);
CREATE TABLE logs_2023_p2 PARTITION OF logs_2023 FOR VALUES WITH (MODULUS 4, REMAINDER 2);
CREATE TABLE logs_2023_p3 PARTITION OF logs_2023 FOR VALUES WITH (MODULUS 4, REMAINDER 3);

-- Note: Dropping logs_2023 drops all its hash partitions instantly.


-- ==========================================
-- 5. Partition Management
-- ==========================================

-- [NOTE] Schema Migration
-- Run ALTER TABLE on the PARENT table. Changes cascade to all partitions automatically.
-- ALTER TABLE orders_range ADD COLUMN customer_note TEXT;

-- Detach a partition (it becomes a standalone table, data is preserved)
-- ALTER TABLE orders_range DETACH PARTITION orders_2020;

-- Attach a partition (must check constraints first)
-- ALTER TABLE orders_range ATTACH PARTITION orders_2020
--     FOR VALUES FROM ('2020-01-01') TO ('2021-01-01');

-- Drop a partition (deletes table and data)
-- DROP TABLE orders_2020;
