-- AUTO_INCREMENT, start from 1
CREATE TABLE animals (
    id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    name CHAR(30) NOT NULL,
    PRIMARY KEY (id)
);

-- get last insert id, connection-specific
SELECT LAST_INSERT_ID();
ALTER TABLE animals AUTO_INCREMENT = 100;

-- Renumbering an Existing Sequence
ALTER TABLE animals DROP id;
ALTER TABLE animals ADD id INT UNSIGNED NOT NULL AUTO_INCREMENT FIRST, ADD PRIMARY KEY (id);
