-- insert
insert INTO pet VALUES ('Puffball','Diane','hamster','f','1999-03-30',NULL);
insert INTO shop VALUES
  (1,'A',3.45), (1,'B',3.99), (2,'A',10.99),
  (3,'B',1.45), (3,'C',1.69), (3,'D',1.25);
insert into my_table values (value1,value2,value3);
insert into my_table (column1,column2,column3) values (value1,value2,value3);
insert into table2 select * from table1;
insert into table2 (column1,column2,column3) select column1,column2,column3 from table1;

-- delete
delete FROM pet;
delete from my_table where some_column = some_value;

-- update
update my_table set filed_name = 'x', filed_name1 = 'x1' where filed_name = 'y';