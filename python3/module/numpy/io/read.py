import numpy as np

# data = np.loadtxt('myfile.txt',
#                   skiprows=1,        #忽略第一行
#                   dtype=np.int,      #数组类型
#                   delimiter=',',     #逗号分割
#                   usecols=(0,1,2,4), #指定使用哪几列数据
#                   comments='%'       #百分号为注释符
#                  )


def general():
    data = np.loadtxt('/tmp/np.test.txt')
    print(data)


def load_as_int():
    data = np.loadtxt('/tmp/np.test.int.txt')
    print(data)


def load_skip_first_row():
    data = np.loadtxt('/tmp/np.test.int.txt', skiprows=1)
    print(data)


def load_as_csv():
    data = np.loadtxt('/tmp/np.test.float.csv', delimiter=',')
    print(data)


def load_as_binary():
    data = np.load('/tmp/np.test.bin.npy')
    print(data)


def load_as_binary_compress():
    data = np.load('/tmp/np.test.npy.npz')
    print(data['a'])


if __name__ == '__main__':
    general()
    load_as_int()
    load_skip_first_row()
    load_as_csv()
    load_as_binary()
    load_as_binary_compress()
