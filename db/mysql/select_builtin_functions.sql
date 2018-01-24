-- aggregation
SELECT SUM(score) FROM t1;
SELECT AVG(score) FROM t1;
SELECT COUNT(score) FROM t1;
SELECT MAX(score) FROM t1;
SELECT MIN(score) FROM t1;

-- string
SELECT CONCAT('FIRST ', 'SECOND');
SELECT CONCAT_WS(',','First name','Last Name' );                        -- with separator
SELECT SUBSTRING('Quadratically',5);
SELECT SUBSTRING('foobarbar' FROM 4);
SELECT SUBSTRING('Quadratically',5,6);
SELECT SUBSTRING_INDEX('www.mysql.com', '.', 2);                        -- www.mysql
SELECT ELT(1, 'ej', 'Heja', 'hej', 'foo');                              -- return strings[i]
SELECT FIELD('ej', 'Hej', 'ej', 'Heja', 'hej', 'foo');                  -- 2 return i which strings[0] = strings[i]
SELECT FIND_IN_SET('b','a,b,c,d');                                      -- 2 sub-string postion
SELECT INSTR('foobarbar', 'bar');                                       -- 4 sub-string postion
SELECT LOCATE('bar', 'foobarbar'), POSITION('bar', 'foobarbar');        -- 4 the position of the first occurrence of substring
SELECT FORMAT(12332.123456, 4);                                         -- '#,###,###.##', rounded to D decimal places
SELECT INSERT('Quadratic', 3, 4, 'What');                               -- QuWhattic  INSERT(str,pos,len,newstr)
SELECT LEFT('foobarbar', 5);                                            -- fooba
SELECT RIGHT('foobarbar', 4);                                           -- rbar
SELECT LOWER('QUADRATICALLY'), UPPER('quadratically');
SELECT LPAD('hi',4,'??');                                               -- ??hi
SELECT RPAD('hi',5,'?');                                                -- hi???
SELECT LTRIM('  barbar');                                               -- barbar
SELECT RTRIM('barbar   ');                                              -- barbar
SELECT TRIM('  bar   ');
SELECT TRIM(LEADING 'x' FROM 'xxxbarxxx');
SELECT TRIM(BOTH 'x' FROM 'xxxbarxxx');
SELECT TRIM(TRAILING 'xyz' FROM 'barxxyz');
SELECT QUOTE('Don\'t!');                                                -- 'Don\'t!'
SELECT CONCAT(id, name, work_date) FROM table1;
SELECT 'ABCDEF' REGEXP 'A%C%%';                                         -- boolean match REGEXP
SELECT REPEAT('MySQL', 3);                                              -- MySQLMySQLMySQL
SELECT REPLACE('www.mysql.com', 'w', 'Ww');                             -- WwWwWw.mysql.com
SELECT REVERSE('abcd');                                                 -- dcba
SELECT SPACE(6);                                                        -- '      '
SELECT STRCMP('MOHD', 'MOHD');                                          -- -1, 0, 1

SELECT ASCII('2');                                                      -- 50
SELECT BIN(12), OCT(12), HEX(255);                                      -- 1100
SELECT BIT_LENGTH('text');                                              -- 32 Returns the length of the string str in bits.
SELECT CHAR_LENGTH("text");                                             -- 4
SELECT LENGTH('text');                                                  -- 4 measured in bytes
SELECT CHAR_LENGTH('我');                                               -- 1
SELECT LENGTH('我');                                                    -- 3
SELECT CHAR(77,121,83,81,'76');                                         -- MySQL
UPDATE table_test SET blob_col=LOAD_FILE('/tmp/picture') WHERE id=1;

-- time
SELECT NOW();

-- date
SELECT CURRENT_DATE;
SELECT CURDATE();
SELECT MONTH(CURRENT_DATE);
SELECT name, birth, CURRENT_DATE, TIMESTAMPDIFF(YEAR, birth, CURRENT_DATE) AS age FROM pet;
select FROM_UNIXTIME(1509550584) valuetime from dual;                   -- convert time_t to datetime
select UNIX_TIMESTAMP("2017-11-01 23:36:24") valuetime from dual;       -- convert datetime to time_t

-- math
SELECT STD(PRICE) STD_DEVIATION FROM CARS;
SELECT ABS(2), MOD(29,3), SQRT(16), EXP(3), POWER(3,3), LOG(45), LOG(2,65536), LOG10(100);
SELECT COS(90), SIN(PI()/4), COT(1), TAN(45), ACOS(1),  ASIN(1), ATAN(1), ATAN2(3,6);
SELECT DEGREES(PI());                                                   -- 180 degree
SELECT CEILING(3.46), FLOOR(7.55);
SELECT CONV(5,16,2);                                                    -- from hex to binary
SELECT RAND(), RAND(), RAND();
SELECT RAND(10), RAND(), RAND();                                        -- seed
SELECT SIGN(-4.65), SIGN(0), SIGN(4.65);
SELECT GREATEST(3,5,1,8,33,99,34,55,67,43), LEAST(3,5,1,8,33,99,34,55,67,43);
SELECT ROUND(5.693893), ROUND(5.693893,2);                              -- 6  5.69
SELECT TRUNCATE(7.536432,2);                                            -- 7.53
SELECT FORMAT(423423234.65434453,2);

-- get last insert id, connection-specific
SELECT LAST_INSERT_ID();

-- admin
SELECT VERSION();                                                       -- Server version string
SELECT DATABASE();                                                      -- Current database name (empty if none)
SELECT USER();                                                          -- Current username
SHOW STATUS;                                                            -- Server status indicators
SHOW VARIABLES;                                                         -- Server configuration variables
