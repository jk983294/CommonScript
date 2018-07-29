import sqlalchemy
from sqlalchemy.orm import sessionmaker
from table_def import *

DB_CON_STR = 'mysql+pymysql://root:123456@localhost/test?charset=utf8'
engine = sqlalchemy.create_engine(DB_CON_STR, echo=False)
Session = sessionmaker(bind=engine)
session = Session()


def get_accounts(id=None, type=None):
    queries = []
    if id:
        queries.append(Accounts.accountid == id)
    if type:
        queries.append(Accounts.type1 == type)

    for a in session.query(Accounts).filter(*queries).all():
        print(a.accountid, a.type1)


get_accounts(id=1, type=1)
get_accounts(type=1)
