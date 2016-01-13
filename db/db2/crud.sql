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

-- select contain but not start with 'x'
select * from my_table where upper(field) like '%x%' and upper(field) not like 'x%' order by field;
-- select max field c
select * from my_table where a = 'a' and b = 'b' order by c desc FETCH FIRST 1 ROWS ONLY;

-- compare two table
with param AS (select 1 as param1, 2 as param2 from dual),
    a AS (select * from table1 as source inner join param on source.param1 = param.param1 and source.param2 = param.param2),
    b AS (select * from table2 as source inner join param on source.param1 = param.param1 and source.param2 = param.param2),
    difftable as (select abs(a.count - b.count) AS COUNT_DIFF, a.param1 from a inner join b on a.param1 = b.param1)
select * from difftable order by COUNT_DIFF desc;


