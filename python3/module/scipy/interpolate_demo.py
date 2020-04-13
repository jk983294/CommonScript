import numpy as np
import scipy as sp
from scipy import interpolate

x = np.arange(6)
y = np.array([0.1, 1.1, 2.1, 3.1, 4.1, 5.1])

# interp1d默认的插值方法是线性插值
model = sp.interpolate.interp1d(x, y)
print(model(3.5))
print(model([3.5, 4.5]))

# kind参数来调节使用的插值方法，来得到不同的结果：
#   nearest 最近邻插值
#   zero 0阶插值
#   linear 线性插值
#   quadratic 二次插值
#   cubic 三次插值
#   4,5,6,7 更高阶插值
model1 = sp.interpolate.interp1d(x, y, kind="nearest")
print(model1([3.2, 4.7]))


# 径向基函数(RBF) radial basis function
# 点 x 处的函数值只依赖于 x 与某点 c 的距离： Φ(x , c) = Φ(|| x − c ||)
model_rbf = sp.interpolate.rbf.Rbf(x, y, function="multiquadric")
print(x, y, model_rbf(x))

# available RBF:
# multiquadric
# gaussian
# inverse_multiquadric
