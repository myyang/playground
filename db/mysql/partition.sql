-- MySQL Partitioning Practice

-- ==========================================
-- 1. Range Partitioning
-- Useful when data falls into a range of values (e.g., dates, IDs).
-- ==========================================

-- Example: Orders table partitioned by year
CREATE TABLE orders_range (
    order_id INT NOT NULL,
    order_date DATE NOT NULL,
    customer_name VARCHAR(100),
    amount DECIMAL(10,2)
)
PARTITION BY RANGE (YEAR(order_date)) (
    PARTITION p0 VALUES LESS THAN (2020),
    PARTITION p1 VALUES LESS THAN (2021),
    PARTITION p2 VALUES LESS THAN (2022),
    PARTITION p3 VALUES LESS THAN (2023),
    PARTITION p4 VALUES LESS THAN MAXVALUE
);

-- [NOTE] Overlap Rules:
-- 1. Range partitions must be strictly increasing. You cannot define p0 < 100, then p1 < 50.
-- 2. If you don't define 'MAXVALUE' and insert a value > 2023, the INSERT will fail with "Table has no partition for value...".
-- 3. NULL values in RANGE partitioning are treated as less than any other value (stored in the first partition).

-- Verify partitions
-- SELECT PARTITION_NAME, TABLE_ROWS FROM INFORMATION_SCHEMA.PARTITIONS WHERE TABLE_NAME = 'orders_range';


-- ==========================================
-- 2. List Partitioning
-- Useful when the partitioning key is a discrete list of values (e.g., categories, regions).
-- ==========================================

-- Example: Users table partitioned by region code
CREATE TABLE users_list (
    user_id INT NOT NULL,
    username VARCHAR(50),
    region_code INT NOT NULL -- 1: East, 2: West, 3: North, 4: South
)
PARTITION BY LIST (region_code) (
    PARTITION p_east VALUES IN (1),
    PARTITION p_west VALUES IN (2),
    PARTITION p_north VALUES IN (3),
    PARTITION p_south VALUES IN (4)
);

-- [NOTE] List Partition Rules:
-- 1. Values cannot be repeated across partitions (e.g., 1 cannot be in p_east and p_west).
-- 2. If you insert a value (e.g., 5) that is not in any list, INSERT fails.
-- 3. Unlike Postgres, MySQL List partitioning generally doesn't support a 'DEFAULT' partition for catching unknown values easily.
-- 4. To handle NULL, you must explicitly include NULL in one of the lists: PARTITION p_null VALUES IN (NULL).


-- ==========================================
-- 3. Hash Partitioning
-- Distributes data evenly across partitions using a hash of the key.
-- ==========================================

-- Example: Logs table partitioned by hashing the log ID
CREATE TABLE logs_hash (
    log_id INT NOT NULL AUTO_INCREMENT,
    message TEXT,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (log_id)
)
PARTITION BY HASH(log_id)
PARTITIONS 4;


-- ==========================================
-- 4. Key Partitioning
-- Similar to Hash, but uses MySQL's internal hashing function (works with strings too).
-- ==========================================

-- Example: Sessions table partitioned by session UUID
CREATE TABLE sessions_key (
    session_id CHAR(36) NOT NULL,
    user_id INT,
    data JSON,
    PRIMARY KEY (session_id)
)
PARTITION BY KEY(session_id)
PARTITIONS 4;


-- ==========================================
-- 5. Subpartitioning (Composite Partitioning)
-- Combine Range (for easy archival) + Hash (for distribution).
-- ==========================================

-- A. Range + Hash
-- Example: Orders partitioned by DATE (Range), then subpartitioned by USER_ID (Hash)
CREATE TABLE orders_composite_hash (
    order_id INT NOT NULL,
    order_date DATE NOT NULL,
    user_id INT NOT NULL,
    amount DECIMAL(10,2)
)
PARTITION BY RANGE(YEAR(order_date))
SUBPARTITION BY HASH(user_id)
SUBPARTITIONS 4 -- Each Range partition will contain 4 Hash subpartitions
(
    PARTITION p2022 VALUES LESS THAN (2023),
    PARTITION p2023 VALUES LESS THAN (2024),
    PARTITION p_future VALUES LESS THAN MAXVALUE
);

-- B. Range + List
-- Example: Sales partitioned by DATE (Range), then subpartitioned by TYPE (List)
-- Note: You must explicitly define subpartitions for EACH partition.
CREATE TABLE sales_composite_list (
    id INT NOT NULL,
    order_date DATE NOT NULL,
    order_type INT NOT NULL, -- 1: Physical, 2: Digital
    amount DECIMAL(10,2)
)
PARTITION BY RANGE(YEAR(order_date))
SUBPARTITION BY LIST(order_type)
(
    -- Range Partition 1: 2022
    PARTITION p2022 VALUES LESS THAN (2023) (
        SUBPARTITION p2022_physical VALUES IN (1),
        SUBPARTITION p2022_digital VALUES IN (2)
    ),
    
    -- Range Partition 2: 2023
    PARTITION p2023 VALUES LESS THAN (2024) (
        SUBPARTITION p2023_physical VALUES IN (1),
        SUBPARTITION p2023_digital VALUES IN (2)
    )
);

-- Note: When you DROP PARTITION p2022, you drop all its subpartitions instantly.


-- ==========================================
-- 6. Partition Management
-- ==========================================

-- ------------------------------------------
-- A. RANGE / LIST Management
-- ------------------------------------------

-- Add a new partition (Range)
-- ALTER TABLE orders_range ADD PARTITION (PARTITION p5 VALUES LESS THAN (2024));

-- Drop a partition (deletes data!)
-- ALTER TABLE orders_range DROP PARTITION p0;

-- Truncate a partition (clears data, keeps partition)
-- ALTER TABLE orders_range TRUNCATE PARTITION p1;

-- [SPLIT] Reorganize partitions (Split p4 into p4 (2023) and p5 (MAXVALUE))
-- ALTER TABLE orders_range REORGANIZE PARTITION p4 INTO (
--     PARTITION p4 VALUES LESS THAN (2023),
--     PARTITION p5 VALUES LESS THAN MAXVALUE
-- );

-- [MERGE] Reorganize partitions (Merge p0 and p1 into a single partition p0_new)
-- Note: The defined range must cover exactly the same range as the partitions being replaced.
-- ALTER TABLE orders_range REORGANIZE PARTITION p0, p1 INTO (
--     PARTITION p0_new VALUES LESS THAN (2021)
-- );


-- ------------------------------------------
-- B. HASH / KEY Management
-- ------------------------------------------

-- [WARNING] ADD/COALESCE for HASH/KEY implies massive data movement (Re-sharding).
-- It acts like a full table rebuild because N changed (MOD N).

-- Reduce number of partitions by 1
-- ALTER TABLE logs_hash COALESCE PARTITION 1;

-- Add 2 new partitions
-- ALTER TABLE logs_hash ADD PARTITION PARTITIONS 2;
