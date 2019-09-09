from guppy import hpy
import random


def random_sort3(n):
    hp = hpy()
    print("Heap at the beginning of the function\n", hp.heap())
    l = [random.random() for i in range(n)]
    l.sort()
    print("Heap at the end of the function\n", hp.heap())
    return l


if __name__ == "__main__":
    random_sort3(2000000)