import sqlalchemy
from sqlalchemy.orm import sessionmaker
from table_def import *

DB_CON_STR = 'mysql+pymysql://root:123456@localhost/test?charset=utf8'
engine = sqlalchemy.create_engine(
    DB_CON_STR, echo=False)  # echo enable verbose logging


Session = sessionmaker(bind=engine)
session = Session()

test1 = MyTest(a='a', b='b')
session.add(test1)
session.add_all([MyTest(a='b', b='c'), MyTest(a='c', b='d')])
session.commit()

t1 = session.query(MyTest).filter_by(a='a').first()
print t1
