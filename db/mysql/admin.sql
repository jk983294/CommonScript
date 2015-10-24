-- connect to server
-- 		mysql -u root -p test
--		mysql -h host -u user -p < batch_file.sql

-- disconnect
--		quit
--		exit

-- ignore current statement
--		\c

-- investigate
USE test;
show databases;
show TABLES;
DESCRIBE pet;
show CREATE TABLE pet;

-- current database
select DATABASE();

-- data import
LOAD DATA LOCAL INFILE '/path/pet.txt' INTO TABLE pet;
LOAD DATA LOCAL INFILE '/path/pet.txt' INTO TABLE pet LINES TERMINATED BY '\r\n';	-- windows specific