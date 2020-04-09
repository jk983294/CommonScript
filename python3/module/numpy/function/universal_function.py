import numpy as np

# ufunc (universal function object) 是能够对数组进行处理的函数

a = np.array([0, 1, 2])
b = np.array([2, 3, 4])
c = np.array([[1, 2, 3], [4, 5, 6]])

print(np.add(a, b))
print(dir(np.add))

# 沿着某个轴应用，使得数组 a 的维数降低一维
print(np.add.reduce(a))  # 3
print(np.add.reduce(c))  # [5 7 9]
print(np.add.reduce(c, 1))  # [6 15]

# accumulate 可以看成保存 reduce 每一步的结果所形成的数组
print(np.add.accumulate(a))  # [0 1 3]

# reduceat 方法将操作符运用到指定的下标range上，返回一个与 indices 大小相同的数组
x = np.array([0, 10, 20, 30, 40, 50])
indices = np.array([1, 4])
print(np.add.reduceat(x, indices))  # 60 = sum(x[1:4]) 90 = sum(x[4:])

# outer, 对于 a 中每个元素，将 op 运用到它和 b 的每一个元素上所得到的结果
a = np.array([0, 1])
b = np.array([1, 2, 3])
print(np.add.outer(a, b))  # [[1 2 3], [2 3 4]]
