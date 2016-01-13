CREATE TABLE schema.table1 (
	"a" VARCHAR(20) NOT NULL,
	"b" VARCHAR(50) NOT NULL,
	"c" INTEGER,
	"d" VARCHAR(20),
	"e" VARCHAR(20),
	"f" TIMESTAMP,
	"g" VARCHAR(20)
)
in PROC_BASE
INDEX in PROC_BASE_IX;

CREATE TABLE schema.table1_temp LIKE schema.table1;

-- drop
drop table schema.table1;
drop PROCEDURE schema.sp_table1_something;
ALTER TABLE schema.table1 DROP PRIMARY KEY;
ALTER TABLE schema.table1 DROP COLUMN column1;

-- alter 
ALTER TABLE schema.table1 RENAME COLUMN UPDATED_BY TO CREATED_BY;
ALTER TABLE schema.table1 ADD new_column VARCHAR(256);
ALTER TABLE schema.table1 ADD CONSTRAINT "table1_PRIMARY_KEY" PRIMARY KEY ("a","b");
ALTER TABLE schema.table1 ALTER COLUMN field1 SET DATA TYPE VARCHAR(200);

-- export, replace 'null' with null
SELECT 'INSERT INTO schema.table1 VALUES ('''
	||a||''', '''                    
	||b||''', '  
	||c||', '''  
	||coalesce(d, 'null')||''', '''  
	||coalesce(e, 'null')||''', current_timestamp, ''prod'' );'                
FROM schema.table1;
