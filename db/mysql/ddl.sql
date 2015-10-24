CREATE DATABASE menagerie;
use menagerie;

CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20), species VARCHAR(20), sex CHAR(1), birth DATE, death DATE);



-- ******************************* alter ************************************
-- column
alter table t1 add(new_column int not null);
alter table t1 drop column new_column;
alter table t1 change old_column new_column int not null;

