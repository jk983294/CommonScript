from dataclasses import dataclass


@dataclass
class Position:
    name: str
    lon: float = 0.0
    lat: float = 0.0


@dataclass
class Capital(Position):
    """
    if a field in a base class has a default value,
    then all new fields added in a subclass must have default values as well.
    """
    country: str = 'Unknown'


if __name__ == '__main__':
    print(Capital('Oslo', 10.8, 59.9, 'Norway'))
