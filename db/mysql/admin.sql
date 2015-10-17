-- connect to server
-- 		mysql -u root -p test
--		mysql -h host -u user -p < batch_file.sql

-- disconnect
--		quit
--		exit

-- ignore current statement
--		\c

-- investigate
show databases;
USE test;
SHOW TABLES;
DESCRIBE pet;

-- current database
SELECT DATABASE();

-- data
LOAD DATA LOCAL INFILE '/path/pet.txt' INTO TABLE pet;
LOAD DATA LOCAL INFILE '/path/pet.txt' INTO TABLE pet LINES TERMINATED BY '\r\n';	-- windows specific


-- select explore
SELECT VERSION(), CURRENT_DATE;
SELECT SIN(PI()/4), (4+1)*5;
SELECT VERSION(); 
SELECT NOW();
SELECT user();