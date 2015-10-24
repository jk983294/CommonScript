-- decoration
select distinct name from t1;
select * from t1 limit 2;
select * from t1 order by name;
select * from t1 order by name desc;
select * from t1 order by name asc;
select name from t1 group by name;

-- *************************** get max row **********************************************
select * FROM my_table WHERE a = (select MAX(a) FROM my_table);
select * FROM my_table ORDER BY price DESC LIMIT 1;
-- only one row have null value because max row value can not less than itself
select s1.* FROM my_table s1 LEFT JOIN my_table s2 ON s1.a < s2.a WHERE s2.a IS NULL;


--  ************************* group ********************************************************
select article, MAX(price) AS max_price FROM shop GROUP BY article having max_price > 10 order by max_price desc;
-- group max
select s1.* FROM shop s1
  JOIN ( select article, MAX(price) AS price FROM shop GROUP BY article) AS s2
    ON s1.article = s2.article AND s1.price = s2.price;
-- Calculating Visits Per Day
select year,month,BIT_COUNT(BIT_OR(1<<day)) AS days FROM t1 GROUP BY year,month;


-- ************************* User-Defined Variables, session-specific, not case sensitive **************
select @min_price:=MIN(price),@max_price:=MAX(price) FROM shop;
select * FROM shop WHERE price=@min_price OR price=@max_price;
SET @t1=1, @t2=2, @t3=4;
select @t1, @t2, @t3, @t4 := @t1+@t2+@t3;


-- ************************* null value *****************************************************
-- cannot use arithmetic comparison operators such as =, <, or <> to test for NULL.
select 1 = NULL, 1 <> NULL, 1 < NULL, 1 > NULL;

-- ************************* like ***********************************************************
select * FROM pet WHERE name LIKE 'b%';
select * FROM pet WHERE name LIKE '_____';		    -- exactly five characters
select * FROM pet WHERE name REGEXP '^.{5}$';
select * FROM pet WHERE name REGEXP '^.....$';	  -- exactly five characters
select * FROM pet WHERE name REGEXP 'w';		      -- contains 'w'

-- ************************* union ***********************************************************
select * FROM test_table WHERE field1_index = '1' UNION select * FROM test_table WHERE field2_index = '1';
