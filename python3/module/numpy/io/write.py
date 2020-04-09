import numpy as np


def general():
    data = np.array([[1, 2], [3, 4]])
    np.savetxt('/tmp/np.test.txt', data)


def save_as_int():
    data = np.array([[1, 2], [3, 4]])
    np.savetxt('/tmp/np.test.int.txt', data, fmt="%d")


def save_as_csv():
    data = np.array([[1, 2], [3, 4]])
    np.savetxt('/tmp/np.test.float.csv', data, fmt="%.2f", delimiter=',')


def save_as_binary():
    data = np.array([[1, 2], [3, 4]])
    np.save('/tmp/np.test.bin.npy', data)


def save_as_binary_compress():
    data = np.array([[1, 2], [3, 4]])
    np.savez_compressed('/tmp/np.test.npy.npz', a=data)


if __name__ == '__main__':
    general()
    save_as_int()
    save_as_csv()
    save_as_binary()
    save_as_binary_compress()
