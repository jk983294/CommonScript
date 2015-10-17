SELECT * FROM pet WHERE name = 'Bowser';
SELECT name, birth FROM pet ORDER BY birth DESC;

-- date calculation
SELECT name, birth, CURDATE(), TIMESTAMPDIFF(YEAR,birth,CURDATE()) AS age FROM pet;
SELECT name, birth, death, TIMESTAMPDIFF(YEAR,birth,death) AS age FROM pet WHERE death IS NOT NULL ORDER BY age;
SELECT name, birth, MONTH(birth) FROM pet;
SELECT name, birth FROM pet WHERE MONTH(birth) = MONTH(DATE_ADD(CURDATE(),INTERVAL 1 MONTH));	-- next month birthday
SELECT name, birth FROM pet WHERE MONTH(birth) = MOD(MONTH(CURDATE()), 12) + 1;

-- null value 
-- cannot use arithmetic comparison operators such as =, <, or <> to test for NULL.
SELECT 1 = NULL, 1 <> NULL, 1 < NULL, 1 > NULL;

-- like
SELECT * FROM pet WHERE name LIKE 'b%';
SELECT * FROM pet WHERE name LIKE '_____';		-- exactly five characters
SELECT * FROM pet WHERE name REGEXP '^.{5}$';
SELECT * FROM pet WHERE name REGEXP '^.....$';	-- exactly five characters
SELECT * FROM pet WHERE name REGEXP 'w';		-- contains 'w'
