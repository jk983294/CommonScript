import sqlalchemy
from sqlalchemy.orm import sessionmaker
from table_def import *
from sqlalchemy import and_
from sqlalchemy import or_
from sqlalchemy import text
from sqlalchemy import func

DB_CON_STR = 'mysql+pymysql://root:123456@localhost/test?charset=utf8'
engine = sqlalchemy.create_engine(
    DB_CON_STR, echo=False)  # echo enable verbose logging
Session = sessionmaker(bind=engine)
session = Session()

for instance in session.query(MyTest).order_by(MyTest.a):
    print(instance.a, instance.b)

for a, b in session.query(MyTest.a, MyTest.b):
    print(a, b)

for row in session.query(MyTest).all():
    print(row.a, row.b)

# select b as new_label from MyTest;
for row in session.query(MyTest.b.label('new_label')).all():
    print(row.new_label)

# select * from MyTest limit 1 offset 1;
for u in session.query(MyTest).order_by(MyTest.a)[1:2]:
    print(u.a, u.b)

# select b from MyTest where a = 'a';
for b, in session.query(MyTest.b).filter_by(a='a'):
    print(b)

# select b from MyTest where a = 'a' and b = 'b';
for b, in session.query(MyTest.b).filter_by(a='a').filter_by(b='b'):
    print(b)

# select * from MyTest top 1;
x = session.query(MyTest).order_by(MyTest.a).first()
print(x.a, x.b)

# common filter condition
# equals:
# query.filter(User.name == 'ed')
# not equals:
# query.filter(User.name != 'ed')
# LIKE:
# query.filter(User.name.like('%ed%'))
# IN:
# query.filter(User.name.in_(['ed', 'wendy', 'jack']))
# NOT IN:
# query.filter(~User.name.in_(['ed', 'wendy', 'jack']))
# IS NULL:
# query.filter(User.name == None)
# IS NOT NULL:
# query.filter(User.name != None)
# AND:
# query.filter(and_(User.name == 'ed', User.fullname == 'Ed Jones'))
# query.filter(User.name == 'ed', User.fullname == 'Ed Jones')
# query.filter(User.name == 'ed').filter(User.fullname == 'Ed Jones')
# OR:
# query.filter(or_(User.name == 'ed', User.name == 'wendy'))

# textual sql
for row in session.query(MyTest).filter(text("a=:v1 and b=:v2")).params(v1='a', v2='b').all():
    print(row.a, row.b)

for row in session.query(MyTest).from_statement(text("SELECT * FROM MyTest where a=:v1")).params(v1='b').all():
    print(row.a, row.b)

stmt = text("SELECT a, b FROM MyTest where a=:v1")
stmt = stmt.columns(MyTest.a, MyTest.b)
for row in session.query(MyTest).from_statement(stmt).params(v1='a').all():
    print(row.a, row.b)


# count
# select count(*) from MyTest where a like '%a';
print(session.query(MyTest).filter(MyTest.a.like('%a')).count())

# select count(*) from MyTest;
print(session.query(func.count('*')).select_from(MyTest).scalar())

# select count(*), a from MyTest group by a;
for row in session.query(func.count(MyTest.a), MyTest.a).group_by(MyTest.a).all():
    print(row)
