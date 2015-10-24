-- aggregation
select sum(score) from t1;
select avg(score) from t1;
select count(score) from t1;
select max(score) from t1;
select min(score) from t1;

-- time
select NOW();

-- date
select CURRENT_DATE;
select CURDATE();
select MONTH(CURRENT_DATE);
select name, birth, CURRENT_DATE, TIMESTAMPDIFF(YEAR, birth, CURRENT_DATE) AS age FROM pet;

-- math
select SIN(PI()/4), (4+1)*5;
select MOD(MONTH(CURRENT_DATE), 12) + 1;

-- get last insert id, connection-specific
select LAST_INSERT_ID();

-- admin
select version();
select user();