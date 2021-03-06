-- *********************** numeric ***************************************
-- INT                  signed : -2147483648 to 2147483647,                                     unsigned : 0 to 4294967295
-- TINYINT              signed : -128 to 127,                                                   unsigned : 0 to 255
-- SMALLINT             signed : -32768 to 32767,                                               unsigned : 0 to 65535
-- MEDIUMINT            signed : -8388608 to 8388607,                                           unsigned : 0 to 16777215
-- BIGINT               signed : -9223372036854775808 to 9223372036854775807,                   unsigned : 0 to 18446744073709551615
-- FLOAT(M,D)           define the display length (M) and the number of decimals (D).           default to 10,2
-- DOUBLE(M,D)          define the display length (M) and the number of decimals (D).           default to 16,4
-- DECIMAL(M,D)

-- *********************** date and time *********************************
-- DATE                 YYYY-MM-DD                                                              1000-01-01 and 9999-12-31
-- DATETIME             YYYY-MM-DD HH:MM:SS                                                     1000-01-01 00:00:00 and 9999-12-31 23:59:59
-- TIMESTAMP            YYYYMMDDHHMMSS                                                          19700101000000 and 2037
-- TIME                 HH:MM:SS
-- YEAR(M)              YEAR(2)        1970 to 2069                            YEAR(4)          1901 to 2155

-- *********************** string ****************************************
-- CHAR(M)              1 and 255
-- VARCHAR(M)           1 and 255
-- BLOB
-- TEXT                 65535 characters, Binary Large Objects, like images or other types of files, case sensitive on BLOBs and not case sensitive in TEXT
-- TINYBLOB
-- TINYTEXT             255 characters
-- MEDIUMBLOB
-- MEDIUMTEXT           16777215 characters
-- LONGBLOB
-- LONGTEXT             4294967295 characters
-- ENUM
