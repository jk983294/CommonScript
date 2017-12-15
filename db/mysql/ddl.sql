-- ******************************* create ************************************
CREATE DATABASE db1;
CREATE TABLE table1 (
    field1 INT NOT NULL AUTO_INCREMENT,
    field2 VARCHAR(100) NOT NULL,
    field3 VARCHAR(40) NOT NULL,
    field4 DATE,
    PRIMARY KEY ( field1 )
) ENGINE = InnoDB DEFAULT CHARSET=utf8;

-- ******************************* clone table ************************************
SHOW CREATE TABLE table1;
-- run creation statement
INSERT INTO clone_table1 (field1, field2, field3, field4) SELECT field1, field2, field3, field4 FROM table1;

-- ******************************* drop ************************************
DROP DATABASE db1;
DROP TABLE table1;

-- ******************************* alter ************************************
-- column
ALTER TABLE table1 ADD (new_column INT NOT NULL);
ALTER TABLE table1 DROP old_column;
ALTER TABLE table1 MODIFY old_column old_column INT;
ALTER TABLE table1 CHANGE old_column new_column INT NOT NULL DEFAULT 100;
ALTER TABLE table1 ALTER column1 SET DEFAULT 1000;
ALTER TABLE table1 ALTER column1 DROP DEFAULT;
-- reposition column, let i follow with c, first drop i, then add it after column c
ALTER TABLE table1 DROP i;
ALTER TABLE table1 ADD i INT AFTER c;
-- table
ALTER TABLE table1 RENAME TO table2;

-- ******************************* INDEX ************************************
SHOW INDEX FROM table1;
CREATE UNIQUE INDEX table1_index ON table1 (field1 DESC);       -- UNIQUE means no duplication
CREATE INDEX table1_index ON table1 (field1 DESC);
ALTER TABLE table1 ADD PRIMARY KEY (column_list);
ALTER TABLE table1 ADD UNIQUE index_name (column_list);
ALTER TABLE table1 ADD INDEX index_name (column_list);
ALTER TABLE table1 ADD FULLTEXT index_name (column_list);
ALTER TABLE table1 DROP PRIMARY KEY;
ALTER TABLE table1 DROP INDEX index_name;

-- ************************* Temporary Tables, session based*************************
CREATE TEMPORARY TABLE temp_table1 (
    field1 VARCHAR(50) NOT NULL,
    field2 DECIMAL(12,2) NOT NULL DEFAULT 0.00,
    field3 DECIMAL(7,2) NOT NULL DEFAULT 0.00,
    field4 INT UNSIGNED NOT NULL DEFAULT 0
);
INSERT INTO temp_table1 (field1, field2, field3, field4) VALUES ('cucumber', 100.25, 90, 2);
DROP TABLE temp_table1;

-- ******************************* Transaction ************************************
SET AUTOCOMMIT=0;           -- turn off auto commit, session based
START TRANSACTION;
SELECT * from table1;
COMMIT;
ROLLBACK;
