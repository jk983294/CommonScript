import numpy as np
from scipy.stats import norm
from scipy.optimize import leastsq, curve_fit


def function(x, a, b, f, phi):
    """a function of x with four parameters"""
    result = a * np.exp(-b * np.sin(f * x + phi))
    return result


def f_err(p, y, x):
    """定义误差函数，将要优化的参数放在前面"""
    return y - function(x, *p)


x = np.linspace(0, 2 * np.pi, 50)
actual_parameters = [3, 2, 1.25, np.pi / 4]
y = function(x, *actual_parameters)
y_noisy = y + 0.8 * norm.rvs(size=len(x))
c, ret_val = leastsq(f_err, [1, 1, 1, 1], args=(y_noisy, x))
print(c, ret_val)  # ret_val 是 1~4 时，表示成功找到最小二乘解


# advanced trick
p_est, err_est = curve_fit(function, x, y_noisy)
print('p_est', p_est)  # 函数的参数
print('err_est', err_est)  # 各个参数的协方差矩阵
print("normalized relative errors for each parameter\n\ta\tb\tf\tphi")
print(np.sqrt(err_est.diagonal()) / p_est)
