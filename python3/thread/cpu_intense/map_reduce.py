import gzip
import io
import glob
from concurrent import futures


"""
futures.ProcessPoolExecutor() will automatically create N python interpreter
N is CPU number
task must be a pure easy function, closure is not supported
result must can be pickled
"""


def find_robots(filename):
    """
    Find all of the hosts that access robots.txt in a single log file
    """
    robots = set()

    with gzip.open(filename) as f:
        for line in io.TextIOWrapper(f, encoding='utf-8'):
            fields = line.split()
            if fields[6] == '/robots.txt':
                robots.add(fields[0])
    return robots


def find_all_robots(logdir):
    """
    Find all hosts across and entire sequence of files
    """
    files = glob.glob(logdir+'/*.log.gz')
    all_robots = set()
    with futures.ProcessPoolExecutor() as pool:
        for robots in pool.map(find_robots, files):
            all_robots.update(robots)   # added into final result
    return all_robots


if __name__ == '__main__':
    robots = find_all_robots('logs')
    for ipaddr in robots:
        print(ipaddr)
