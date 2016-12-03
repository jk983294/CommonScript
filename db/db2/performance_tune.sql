-- get each ID's max day's FIELD4, using group by is 10 times better
select a.ID, a.FIELD4 from SCHEMA.MY_TABLE a
	where a.DATE_KEY = (SELECT MAX(DATE_KEY) FROM SCHEMA.MY_TABLE where ID = a.ID) and
      a.FIELD2 = 'FIELD2' and a.FIELD3 = 'FIELD3';

select a.ID, a.FIELD4 from SCHEMA.MY_TABLE a inner join
  	(SELECT MAX(DATE_KEY) as DATE_KEY, ID FROM SCHEMA.MY_TABLE group by ID) b
  		on a.DATE_KEY = b.DATE_KEY and a.ID = b.ID
  			where a.FIELD2 = 'FIELD2' and a.FIELD3 = 'FIELD3';