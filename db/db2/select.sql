-- select contain but not start with 'x'
select * from my_table where upper(field) like '%x%' and upper(field) not like 'x%' order by field;

-- select max field c
select * from my_table where a = 'a' and b = 'b' order by c desc FETCH FIRST 1 ROWS ONLY;



