from dataclasses import dataclass, field, fields
from typing import Any, List
from math import asin, cos, radians, sin, sqrt


RANKS = '2 3 4 5 6 7 8 9 10 J Q K A'.split()
SUITS = '♣ ♢ ♡ ♠'.split()


def make_french_deck():
    return [PlayingCard(r, s) for s in SUITS for r in RANKS]


@dataclass(order=True)
class PlayingCard:
    sort_index: int = field(init=False, repr=False)  # not init first, will be post init
    rank: str
    suit: str

    def __post_init__(self):
        """this field should be calculated after the other fields init"""
        self.sort_index = (RANKS.index(self.rank) * len(SUITS) + SUITS.index(self.suit))

    def __str__(self):
        return f'{self.suit}{self.rank}'


@dataclass
class Deck:
    """default_factory to handle mutable default values"""
    cards: List[PlayingCard] = field(default_factory=make_french_deck)

    def __repr__(self):
        cards = ', '.join(f'{c!s}' for c in self.cards)
        return f'{self.__class__.__name__}({cards})'


@dataclass
class Position:
    name: str
    lon: float = 0.0
    lat: float = 0.0  # default values
    height: float = field(default=0.0, metadata={'unit': 'meters'})

    def distance_to(self, other):
        r = 6371  # Earth radius in kilometers
        lam_1, lam_2 = radians(self.lon), radians(other.lon)
        phi_1, phi_2 = radians(self.lat), radians(other.lat)
        h = (sin((phi_2 - phi_1) / 2) ** 2 + cos(phi_1) * cos(phi_2) * sin((lam_2 - lam_1) / 2) ** 2)
        return 2 * r * asin(sqrt(h))


@dataclass
class WithoutExplicitTypes:
    name: Any
    value: Any = 42


if __name__ == '__main__':
    queen_of_hearts = PlayingCard('Q', '♡')
    print(queen_of_hearts.rank)  # 'Q'
    print(queen_of_hearts)  # PlayingCard(rank='Q', suit='♡')
    print(queen_of_hearts == PlayingCard('Q', '♡'))  # True
    ace_of_spades = PlayingCard('A', '♢')
    two_cards = Deck([queen_of_hearts, ace_of_spades])
    print(ace_of_spades > queen_of_hearts)   # @dataclass(order=True)
    print(two_cards)
    whole_cards = Deck()
    print(whole_cards)

    pos = Position('Oslo', 10.8, 59.9)
    vancouver = Position('Vancouver', -123.1, 49.3)
    print(pos)  # Position(name='Oslo', lon=10.8, lat=59.9)
    print(pos.lat)  # 59.9
    print(Position('Null Island'))  # Position(name='Null Island', lon=0.0, lat=0.0)

    print(pos.distance_to(vancouver))

    print(fields(Position))   # (Field(name='name',type=<class 'str'> ...
    print(fields(Position)[3].metadata['unit'])  # meters
