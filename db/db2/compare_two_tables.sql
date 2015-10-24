-- compare two table
with param AS (select 1 as param1, 2 as param2 from dual),
    a AS (select * from table1 as source inner join param on source.param1 = param.param1 and source.param2 = param.param2),
    b AS (select * from table2 as source inner join param on source.param1 = param.param1 and source.param2 = param.param2),
    difftable as (select abs(a.count - b.count) AS COUNT_DIFF, a.param1 from a inner join b on a.param1 = b.param1)
select * from difftable order by COUNT_DIFF desc;


