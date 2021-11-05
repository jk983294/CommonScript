import pyarrow.plasma as plasma

if __name__ == '__main__':
    client_ = plasma.connect("/tmp/plasma")
    for d in client_.list():
        print(d)
