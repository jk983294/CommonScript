-- AUTO_INCREMENT, start from 1
CREATE TABLE animals (
  id INT NOT NULL AUTO_INCREMENT,
  name CHAR(30) NOT NULL,
  PRIMARY KEY (id)
);

-- get last insert id, connection-specific
select LAST_INSERT_ID();