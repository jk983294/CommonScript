import requests
from multiprocessing import Pool


def get_website_data(url):
    r = requests.get(url)
    return r.url


def main():
    urls = ['http://www.qq.com',
            'http://www.baidu.com',
            'http://www.163.com']
    pool = Pool(2)
    print(pool.map(get_website_data, urls))


main()
