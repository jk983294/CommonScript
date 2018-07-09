import sqlalchemy
from sqlalchemy.orm import sessionmaker
from table_def import *
from sqlalchemy.orm import aliased
from sqlalchemy.sql import exists

DB_CON_STR = 'mysql+pymysql://root:123456@localhost/test?charset=utf8'
engine = sqlalchemy.create_engine(
    DB_CON_STR, echo=True)  # echo enable verbose logging
Session = sessionmaker(bind=engine)
session = Session()


# select Accounts.*, StrategyAccount.* from Accounts, StrategyAccount
# where Accounts.accountid = StrategyAccount.AccountID;
for a, s in session.query(Accounts, StrategyAccount).filter(Accounts.accountid == StrategyAccount.AccountID).all():
    print(a.accountid, a.type1, s.StrategyID)

# SELECT Accounts.*, StrategyAccount.* FROM Accounts INNER JOIN StrategyAccount
# ON Accounts.accountid = StrategyAccount.AccountID
for a, s in session.query(Accounts, StrategyAccount).join(StrategyAccount, Accounts.accountid == StrategyAccount.AccountID).all():
    print(a.accountid, a.type1)

for a, s in session.query(Accounts, StrategyAccount).select_from(Accounts).\
        join(StrategyAccount, Accounts.accountid == StrategyAccount.AccountID).all():
    print(a.accountid, a.type1, s.StrategyID)

# SELECT Accounts.*, StrategyAccount.* FROM Accounts INNER JOIN StrategyAccount
# ON Accounts.accountid = StrategyAccount.AccountID INNER JOIN StrategyHist
# ON StrategyAccount.StrategyID = StrategyHist.StrategyID
for a, s, h in session.query(Accounts, StrategyAccount, StrategyHist).select_from(Accounts).\
        join(StrategyAccount, Accounts.accountid == StrategyAccount.AccountID).\
        join(StrategyHist, StrategyAccount.StrategyID == StrategyHist.StrategyID).all():
    print(a.accountid, a.type1, s.StrategyID, h.Type1)

# subquery
# select Accounts.*, sa.* from Accounts INNER JOIN (select * from StrategyAccount) as sa
# on Accounts.accountid = sa.AccountID;
stmt = session.query(StrategyAccount).subquery()
saalias = aliased(StrategyAccount, stmt)
for a, s in session.query(Accounts, saalias).select_from(Accounts).\
        join(saalias, Accounts.accountid == saalias.AccountID).all():
    print(a.accountid, a.type1, s.StrategyID)

# exists
# select Accounts.accountid from Accounts where exists (select * from StrategyAccount
# where Accounts.accountid = StrategyAccount.AccountID);
stmt = exists().where(Accounts.accountid == StrategyAccount.AccountID)
for a in session.query(Accounts.accountid).filter(stmt).all():
    print(a.accountid)
