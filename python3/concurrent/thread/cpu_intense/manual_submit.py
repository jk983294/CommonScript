from concurrent import futures


"""
futures.ProcessPoolExecutor() will automatically create N python interpreter
N is CPU number
task must be a pure easy function, closure is not supported
result must can be pickled
"""


total = 0


def calculate_number(number):
    return number * number


def finish_callback(r):
    global total
    tmpResult = r.result()
    total += tmpResult
    print('Got:', tmpResult)


def calculate_all_numbers(num):
    """
    Find all hosts across and entire sequence of files
    """
    numbers = range(num)
    with futures.ProcessPoolExecutor() as pool:
        for number in numbers:
            future_result = pool.submit(calculate_number, number)
            future_result.add_done_callback(finish_callback)


if __name__ == '__main__':
    calculate_all_numbers(10)
    print(total)

