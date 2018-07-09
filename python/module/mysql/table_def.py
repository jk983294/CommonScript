import sqlalchemy
from sqlalchemy.ext.declarative import declarative_base
sqlalchemyBase = declarative_base()


class MyTest(sqlalchemyBase):
    __tablename__ = 'MyTest'
    a = sqlalchemy.Column(sqlalchemy.String(30), primary_key=True)
    b = sqlalchemy.Column(sqlalchemy.String(30))


class StrategyAccount(sqlalchemyBase):
    __tablename__ = 'StrategyAccount'
    StrategyID = sqlalchemy.Column(sqlalchemy.String(30), primary_key=True)
    AccountID = sqlalchemy.Column(sqlalchemy.String(30), primary_key=True)


class Accounts(sqlalchemyBase):
    __tablename__ = 'Accounts'
    accountid = sqlalchemy.Column(sqlalchemy.String(30), primary_key=True)
    type1 = sqlalchemy.Column(sqlalchemy.String(30))


class StrategyHist(sqlalchemyBase):
    __tablename__ = 'StrategyHist'
    ID = sqlalchemy.Column(sqlalchemy.Integer, primary_key=True)
    StrategyID = sqlalchemy.Column(sqlalchemy.String(30))
    Type1 = sqlalchemy.Column(sqlalchemy.String(30))
