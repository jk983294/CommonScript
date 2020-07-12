from typing import List, Sequence
from peewee import MySQLDatabase, Model, AutoField, CharField, DateTimeField, FloatField, chunked
from datetime import datetime
from dataclasses import dataclass
from enum import Enum


def init_mysql():
    settings = {
        "database": "Phoenix",
        "user": "kun",
        "password": "123456",
        "host": "localhost",
        "port": 3306
    }
    db_ = MySQLDatabase(**settings)
    return db_


db = init_mysql()


class Exchange(Enum):
    CFFEX = "CFFEX"         # China Financial Futures Exchange
    SHFE = "SHFE"           # Shanghai Futures Exchange
    CZCE = "CZCE"           # Zhengzhou Commodity Exchange
    DCE = "DCE"             # Dalian Commodity Exchange
    INE = "INE"             # Shanghai International Energy Exchange
    SSE = "SSE"             # Shanghai Stock Exchange
    SZSE = "SZSE"           # Shenzhen Stock Exchange


class Interval(Enum):
    MINUTE = "1m"
    HOUR = "1h"
    DAILY = "d"
    WEEKLY = "w"


@dataclass
class BarData:
    symbol: str
    exchange: Exchange
    datetime: datetime

    interval: Interval = None
    volume: float = 0
    open_interest: float = 0
    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    close_price: float = 0

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


class ModelBase(Model):
    def to_dict(self):
        return self.__data__


class DbBarData(ModelBase):
    """
    Candlestick bar data for database storage.

    Index is defined unique with datetime, interval, symbol
    """

    id = AutoField()
    symbol: str = CharField()
    exchange: str = CharField()
    datetime: datetime = DateTimeField()
    interval: str = CharField()

    volume: float = FloatField()
    open_interest: float = FloatField()
    open_price: float = FloatField()
    high_price: float = FloatField()
    low_price: float = FloatField()
    close_price: float = FloatField()

    class Meta:
        database = db
        indexes = ((("symbol", "exchange", "interval", "datetime"), True),)

    @staticmethod
    def from_bar(bar: BarData):
        """
        Generate DbBarData object from BarData.
        """
        db_bar = DbBarData()

        db_bar.symbol = bar.symbol
        db_bar.exchange = bar.exchange.value
        db_bar.datetime = bar.datetime.astimezone()
        db_bar.interval = bar.interval.value
        db_bar.volume = bar.volume
        db_bar.open_interest = bar.open_interest
        db_bar.open_price = bar.open_price
        db_bar.high_price = bar.high_price
        db_bar.low_price = bar.low_price
        db_bar.close_price = bar.close_price

        return db_bar

    def to_bar(self):
        """
        Generate BarData object from DbBarData.
        """
        bar = BarData(
            symbol=self.symbol,
            exchange=Exchange(self.exchange),
            datetime=self.datetime.replace(),
            interval=Interval(self.interval),
            volume=self.volume,
            open_price=self.open_price,
            high_price=self.high_price,
            open_interest=self.open_interest,
            low_price=self.low_price,
            close_price=self.close_price
        )
        return bar

    @staticmethod
    def save_all(objs: List["DbBarData"]):
        """
        save a list of objects, update if exists.
        """
        dicts = [i.to_dict() for i in objs]
        with db.atomic():
            for c in chunked(dicts, 50):
                DbBarData.insert_many(c).on_conflict_replace().execute()


def save_bar_data(datum: Sequence[BarData]):
    ds = [DbBarData.from_bar(i) for i in datum]
    DbBarData.save_all(ds)


def load_bar_data(
    symbol: str,
    exchange: Exchange
) -> Sequence[BarData]:
    s = (
        DbBarData.select().where(
            (DbBarData.symbol == symbol)
            & (DbBarData.exchange == exchange.value)
        )
        .order_by(DbBarData.datetime)
    )
    data = [db_bar.to_bar() for db_bar in s]
    return data


def test_save():
    ret = []
    for i in range(10):
        bar = BarData(
            symbol=str(i),
            exchange=Exchange.CFFEX,
            datetime=datetime.today(),
            interval=Interval.MINUTE,
            volume=i,
            open_price=i,
            high_price=i,
            open_interest=i,
            low_price=i,
            close_price=i
        )
        ret.append(bar)
    save_bar_data(ret)


db.connect()
db.create_tables([DbBarData])
# test_save()
print(load_bar_data(symbol='1', exchange=Exchange.CFFEX))
