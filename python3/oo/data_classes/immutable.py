from dataclasses import dataclass
from typing import List


@dataclass(frozen=True)
class Position:
    name: str
    lon: float = 0.0
    lat: float = 0.0


@dataclass(frozen=True)
class ImmutableCard:
    rank: str
    suit: str


@dataclass(frozen=True)
class ImmutableDeck:
    cards: List[ImmutableCard]


if __name__ == '__main__':
    pos = Position('Oslo', 10.8, 59.9)
    print(pos.name)

    # pos.name = 'Stockholm'  # dataclasses.FrozenInstanceError: cannot assign to field 'name'
