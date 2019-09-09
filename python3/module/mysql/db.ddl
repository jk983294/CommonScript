mysql -u root -p mysql
CREATE DATABASE test;
use test;

CREATE TABLE Accounts (
    accountid VARCHAR(30) NOT NULL,
    type1 VARCHAR(30),
    PRIMARY KEY ( accountid )
) ENGINE = InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE StrategyAccount (
    StrategyID VARCHAR(30) NOT NULL,
    AccountID VARCHAR(30) NOT NULL,
    PRIMARY KEY ( StrategyID, AccountID )
) ENGINE = InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE StrategyHist (
    ID INT NOT NULL AUTO_INCREMENT,
    StrategyID VARCHAR(30) NOT NULL,
    Type1 VARCHAR(30),
    PRIMARY KEY ( ID )
) ENGINE = InnoDB DEFAULT CHARSET=utf8;

INSERT INTO Accounts (accountid, type1) VALUES ('1', '1');
INSERT INTO Accounts (accountid, type1) VALUES ('2', '2');
INSERT INTO Accounts (accountid, type1) VALUES ('3', '1');

DELETE FROM StrategyAccount;
INSERT INTO StrategyAccount (StrategyID, AccountID) VALUES ('alpha1_1', '1');
INSERT INTO StrategyAccount (StrategyID, AccountID) VALUES ('alpha1_2', '1');
INSERT INTO StrategyAccount (StrategyID, AccountID) VALUES ('alpha2_1', '2');
INSERT INTO StrategyAccount (StrategyID, AccountID) VALUES ('alpha3_1', '3');

INSERT INTO StrategyHist (StrategyID, Type1) VALUES ('alpha1_1', '1');
INSERT INTO StrategyHist (StrategyID, Type1) VALUES ('alpha1_2', '2');
INSERT INTO StrategyHist (StrategyID, Type1) VALUES ('alpha2_1', null);
INSERT INTO StrategyHist (StrategyID, Type1) VALUES ('alpha3_1', '1');


CREATE TABLE MyTest (
    a VARCHAR(30) NOT NULL,
    b VARCHAR(30),
    PRIMARY KEY ( a )
) ENGINE = InnoDB DEFAULT CHARSET=utf8;
