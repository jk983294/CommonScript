import cvxpy as cp

x = cp.Variable((5, 4))
y = cp.Variable((5, 4))
c = cp.Variable()
p = 3
alpha = 1.0
beta = 2.0

cp.abs(x)    # |x|
cp.entr(x)    # −xlog(x)
cp.exp(x)    # e^x
cp.huber(x, M=1)    # x^2 if |x|≤M else  2M|x|−M^2 if |x|>M
cp.inv_pos(x)    # 1/x
cp.kl_div(x, y)    # xlog(x/y)−x+y
cp.log(x)    # log(x)
cp.log1p(x)    # log(x+1)
cp.logistic(x)    # log(1+e^x)
cp.maximum(x, y)    # max{x,y}
cp.minimum(x, y)    # min{x,y}
cp.multiply(c, x)    # c*x
cp.neg(x)    # max{−x,0}
cp.pos(x)    # max{x,0}
cp.power(x, 0)    # 1
cp.power(x, p)    # x^p
cp.scalene(x, alpha, beta)    # αpos(x)+βneg(x)
cp.sqrt(x)
cp.square(x)    # x^2
