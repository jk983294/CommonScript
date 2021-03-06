-- insert
insert into my_table values (value1,value2,value3);
insert into my_table (column1,column2,column3) values (value1,value2,value3);
insert into table2 select * from table1;
insert into table2 (column1,column2,column3) select column1,column2,column3 from table1;
insert into table2 values ('first'||chr(10)||'last');    -- insert with \n

-- delete
delete from my_table where some_column = some_value;

-- update
update my_table set filed_name = 'x', filed_name1 = 'x1' where filed_name = 'y';
UPDATE table1 t1 SET (col1, col2) = (SELECT col3, col4 FROM  table2 t2 WHERE t1.col8=t2.col9);
UPDATE schema.my_table dest SET SUM_FIELD1 =
	(SELECT src.SUM_FIELD1 FROM
		(SELECT field2, field3, SUM(field1) AS SUM_FIELD1 FROM schema.my_table GROUP BY field2, field3) src
			WHERE src.field2 = dest.field2 AND src.field3 = dest.field3);
-- update target row based on source row
UPDATE schema.my_table t1 SET (field1, field2) =
    (SELECT field1, field2 FROM schema.my_table t2 WHERE t2.field3 = P_SOURCE and t2.field4 = P_FIELD4)
    WHERE t1.field3 = P_TARGET and t1.field4 = P_FIELD4;

-- select contain but not start with 'x'
select * from my_table where upper(field) like '%x%' and upper(field) not like 'x%' order by field;
-- select max field c
select * from my_table where a = 'a' and b = 'b' order by c desc FETCH FIRST 1 ROWS ONLY;
-- select DISTINCT on multiple columns
SELECT a,b,c FROM t GROUP BY a,b,c
-- inner join multiply table
SELECT s.*, hp.field1, h.field2 FROM table1 s INNER JOIN table2 hp on s.field1 = hp.field1
    INNER JOIN table3 h on hp.field2 = h.field2;

-- compare two table
with param AS (select 1 as param1, 2 as param2 from dual),
    a AS (select * from table1 as source inner join param on source.param1 = param.param1 and source.param2 = param.param2),
    b AS (select * from table2 as source inner join param on source.param1 = param.param1 and source.param2 = param.param2),
    difftable as (select abs(a.count - b.count) AS COUNT_DIFF, a.param1 from a inner join b on a.param1 = b.param1)
select * from difftable order by COUNT_DIFF desc;


