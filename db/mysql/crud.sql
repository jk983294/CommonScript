-- INSERT
INSERT INTO table1 VALUES ('filed1','filed2','1999-03-30',NULL);
REPLACE INTO table1 VALUES ('filed1','filed2','1999-03-30',NULL);               -- upsert
INSERT IGNORE INTO table1 VALUES ('filed1','filed2','1999-03-30',NULL);         -- if duplicate, discard it silently without generating an error
INSERT INTO table1 VALUES (1,'filed1'), (2,'filed2'), (3,'filed3');
INSERT INTO table1 VALUES (value1,value2,value3);
INSERT INTO table1 (column1,column2,column3) VALUES (value1,value2,value3);
INSERT INTO table1 SELECT * FROM table2;
INSERT INTO table1 (column1,column2,column3) SELECT column1,column2,column3 FROM table2;

-- DELETE
DELETE FROM table1;
DELETE FROM table1 WHERE filed1 = 'filed1';

-- UPDATE
UPDATE table1 SET filed1 = 'filed1', filed2 = 'filed2' WHERE filed3 = 'filed3';
