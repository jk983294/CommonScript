-- decoration
SELECT * FROM table1 LIMIT 2 OFFSET 5;
SELECT * FROM table1 ORDER BY column1;
SELECT * FROM table1 ORDER BY column1, column2 DESC;
SELECT * FROM table1 ORDER BY column1 ASC;
SELECT * FROM table1 ORDER BY RAND();					                  -- random order
SELECT COUNT(*), column1 FROM table1 GROUP BY column1;
SELECT DISTINCT name FROM t1;

-- WHERE clause
SELECT * FROM table1 WHERE field1 = 'field1';			              -- case insensitive
SELECT * FROM table1 WHERE BINARY field1 = 'field1';	          -- case sensitive
SELECT * FROM table1 WHERE field1 LIKE 'field1%';
SELECT * FROM table1 WHERE field2 IN ( 250, 220, 170 );
SELECT * FROM table1 WHERE field2 BETWEEN 170 AND 300; 

-- JOIN
SELECT a.field1, a.field2, b.field3 FROM table1 a, table2 b WHERE a.field1 = b.field1;
SELECT a.field1, a.field2, b.field3 FROM table1 a INNER JOIN table2 b ON a.field1 = b.field1;
SELECT a.field1, a.field2, b.field3 FROM table1 a LEFT JOIN table2 b ON a.field1 = b.field1;

-- ************************* null value *****************************************************
SELECT 1 = NULL, 1 <> NULL, 1 < NULL, 1 > NULL;	                -- cannot use arithmetic comparison operators such as =, <, or <> to test for NULL.
SELECT NULL <=> NULL, 1 <=> NULL;
SELECT * FROM table1 WHERE field1 IS NULL;
SELECT * FROM table1 WHERE field1 IS NOT NULL;

-- ************************* LIKE REGEXP ***********************************************************
SELECT * FROM table1 WHERE field1 LIKE 'b%';
SELECT * FROM table1 WHERE field1 LIKE '_____';		    			    -- exactly five characters
SELECT * FROM table1 WHERE field1 REGEXP '^.{5}$';					    -- exactly five characters
SELECT * FROM table1 WHERE field1 REGEXP '^.....$';	  				  -- exactly five characters
SELECT * FROM table1 WHERE field1 REGEXP '^st';						      -- starting with 'st'
SELECT * FROM table1 WHERE field1 REGEXP 'ok$';						      -- ending with 'ok'
SELECT * FROM table1 WHERE field1 REGEXP 'mar';						      -- contains 'mar'
SELECT * FROM table1 WHERE field1 REGEXP '^[aeiou].*ok$';			  -- starting with a vowel and ending with 'ok'
-- ^			    Beginning of string
-- $			    End of string
-- .			    Any single character
-- [...]		  Any character listed between the square brackets
-- [^...]		  Any character not listed between the square brackets
-- p1|p2|p3		Alternation; matches any of the patterns p1, p2, or p3
-- *			    Zero or more instances of preceding element
-- +			    One or more instances of preceding element
-- {n}			  n instances of preceding element
-- {m,n}		  m through n instances of preceding element


-- *************************** get max row **********************************************
SELECT * FROM my_table WHERE a = (SELECT MAX(a) FROM my_table);
SELECT * FROM my_table ORDER BY price DESC LIMIT 1;
-- only one row have null value because max row value can not less than itself
SELECT s1.* FROM my_table s1 LEFT JOIN my_table s2 ON s1.a < s2.a WHERE s2.a IS NULL;


--  ************************* group ********************************************************
SELECT article, MAX(price) AS max_price FROM shop GROUP BY article having max_price > 10 ORDER BY max_price DESC;
-- group max
SELECT s1.* FROM shop s1
  JOIN ( SELECT article, MAX(price) AS price FROM shop GROUP BY article) AS s2
    ON s1.article = s2.article AND s1.price = s2.price;
-- Calculating Visits Per Day
SELECT year,month,BIT_COUNT(BIT_OR(1<<day)) AS days FROM t1 GROUP BY year,month;

--  ************************* Duplicates ******************************************************** 
SELECT COUNT(*) as repetitions, last_name, first_name FROM person_tbl GROUP BY last_name, first_name HAVING repetitions > 1; -- Counting and Identifying 
-- remove duplicates method1
CREATE TABLE tmp SELECT last_name, first_name, sex FROM person_tbl GROUP BY (last_name, first_name);
DROP TABLE person_tbl;
ALTER TABLE tmp RENAME TO person_tbl;
-- remove duplicates method2
ALTER IGNORE TABLE person_tbl ADD PRIMARY KEY (last_name, first_name);
    
-- ************************* User-Defined Variables, session-specific, not case sensitive **************
SELECT @min_price:=MIN(price),@max_price:=MAX(price) FROM shop;
SELECT * FROM shop WHERE price=@min_price OR price=@max_price;
SET @t1=1, @t2=2, @t3=4;
SELECT @t1, @t2, @t3, @t4 := @t1+@t2+@t3;


-- ************************* union ***********************************************************
SELECT * FROM test_table WHERE field1_index = '1' UNION SELECT * FROM test_table WHERE field2_index = '1';
