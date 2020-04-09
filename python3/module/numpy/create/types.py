import numpy as np


# 基本类型	可用的Numpy类型	                                备注
# 布尔型	    bool	                                        占1个字节
# 整型	    int8, int16, int32, int64, int128, int	        int 跟C语言中的 long 一样大
# 无符号整型	uint8, uint16, uint32, uint64, uint128, uint	uint 跟C语言中的 unsigned long 一样大
# 浮点数	    float16, float32, float64, float, longfloat	    默认为双精度 float64 ，longfloat 精度大小与系统有关
# 复数	    complex64, complex128, complex, longcomplex	    默认为 complex128 ，即实部虚部都为双精度
# 字符串	    string, unicode	                                可以使用 dtype=S4 表示一个4字节字符串的数组
# 对象	    object	                                        数组中可以使用任意值
# Records	void
# 时间	    datetime64, timedelta64

a = np.array([1, 1.2, 'hello', [1, 2]], dtype=object)
print(a * 2)        # [2 2.4 'hellohello' list([1, 2, 1, 2])]

# type conversion
# asarray不会修改原来数组的值, 但当类型相同的时候，asarray并不会产生新的对象，而是使用同一个引用
a = np.array([1.5, -3], dtype=np.float32)
print(np.asarray(a, dtype=np.float64))
# astype 方法返回一个新数组, 不会改变原来数组的值, 总是返回原来数组的一份复制，即使转换的类型是相同的
print(a.astype(dtype=np.float64))
# view会将a在内存中的表示看成是uint8进行解析, view共用一块内存
b = np.array((1, 2), dtype=np.int32)
print(a.view(np.uint8))
