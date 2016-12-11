-- select contain but not start with 'x'
select * from my_table where upper(field) like '%x%' and upper(field) not like 'x%' order by field;

-- select max field c
select * from my_table where a = 'a' and b = 'b' order by c desc FETCH FIRST 1 ROWS ONLY;

-- find max FIELD1's max FIELD2's of all IDs, result set [ID, FIELD1, FIELD2]
-- the idea is to construct max_key using FIELD1 + FIELD2, then group by that max_key
WITH myIds AS (SELECT my.ID, my.FIELD1, my.FIELD2, (my.FIELD1 * 100 + my.FIELD2) max_two_fields_key FROM SCHEMA.MY_TABLE my)
SELECT myIds.* FROM myIds INNER JOIN (SELECT ID, max(max_two_fields_key) max_two_fields_key FROM myIds GROUP BY ID) b
	ON myIds.ID = b.ID AND myIds.max_two_fields_key = b.max_two_fields_key;


