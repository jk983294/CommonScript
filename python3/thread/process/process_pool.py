from multiprocessing import Pool
import multiprocessing
import time
import os


def f(x):
    return x*x


if __name__ == '__main__':
    # start 4 worker processes
    with Pool(processes=4) as pool:
        # print "[0, 1, 4,..., 81]"
        print(pool.map(f, range(10)))

        # print same numbers in arbitrary order
        for i in pool.imap_unordered(f, range(10)):
            print(i)

        # evaluate "f(20)" synchronously
        res = pool.apply(f, (20,))  # runs in *only* one process
        print("f(20) synchronously", res)  # prints "400"

        # evaluate "f(20)" asynchronously
        res = pool.apply_async(f, (20,))                    # runs in *only* one process
        print("f(20) asynchronously", res.get(timeout=1))                  # prints "400"

        # evaluate "os.getpid()" asynchronously
        res = pool.apply_async(os.getpid, ())               # runs in *only* one process
        print("os.getpid()", res.get(timeout=1))            # prints the PID of that process

        # launching multiple evaluations asynchronously *may* use more processes
        multiple_results = [pool.apply_async(os.getpid, ()) for i in range(4)]
        print([res.get(timeout=1) for res in multiple_results])

        # make a single worker sleep for 10 secs
        res = pool.apply_async(time.sleep, (10,))
        try:
            print(res.get(timeout=1))
        except multiprocessing.context.TimeoutError:
            print("We lacked patience and got a multiprocessing.TimeoutError")

        print("For the moment, the pool remains available for more work")

    # exiting the 'with'-block has stopped the pool
    print("Now the pool is closed and no longer available")
