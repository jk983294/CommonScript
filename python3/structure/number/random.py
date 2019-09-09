import random


list1 = [1, 2, 3, 4, 5]

# random number
# Sets the integer starting value used in generating random numbers.
# Call this function before calling any other random module function. Returns None.
random.seed(5)

# A random item from a list, tuple, or string.
print(random.choice([1, 2, 4]))

# A randomly selected element from range(start, stop, step), step is 2 means only odd number to be returned
print(random.randrange(1, 10, 2))

# A random float r, such that r belongs [0, 1]
print(random.random())
# random number [0, n]
print(random.randint(0, 10))

# randomly sample from list
random.sample(list1, 2)
random.sample(list1, 3)

# Randomizes the items of a list in place. Returns None.
random.shuffle(list1)
print(list1)

# A random float r, such that x is less than or equal to r and r is less than y
print(random.uniform(1.0, 5.0))
