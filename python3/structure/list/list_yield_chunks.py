import pprint


def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]


pprint.pprint(list(chunks(range(10, 75), 10)))
