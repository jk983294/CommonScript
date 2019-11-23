import cvxpy as cp

k = 3
p = cp.Variable()
x = cp.Variable(5)
A = cp.Variable((5, 5))

# apply for vector
cp.geo_mean(x)    # pi ( x_i^(1/n) )
cp.harmonic_mean(x)    # n / (sigma (1/x_i))
cp.tv(x)    # ∑|x[i+1]−x[i]|, total variation, L1 norm of discrete gradients for vectors

# apply for matrix
cp.lambda_max(A)    # max eigen value
cp.lambda_min(A)    # min eigen value
cp.lambda_sum_largest(A, k)    # sum of k largest eigen values
cp.lambda_sum_smallest(A, k)    # sum of k smallest eigen values
cp.log_det(A)    # log(det(A))
cp.log_sum_exp(A)    # log(∑e^A[i,j])
cp.matrix_frac(x, A)    # x^T P^(−1) x
cp.max(A)    # max{A[i,j]}
cp.min(A)    # min{A[i,j]}
cp.quad_over_lin(A, p)    # (∑A[i,j]^2)/p
cp.sum(A)    # ∑A[i,j]
cp.sum_largest(A, k)    # sum of k largest A[i,j]
cp.sum_smallest(A, k)    # sum of k smallest  A[i,j]
cp.sum_squares(A)    # ∑A[i,j]^2
cp.trace(A)    # tr(A)
cp.tv(A)    # total variation, L2 norm of discrete gradients for matrices

# norm
cp.norm(x)    # sqrt(∑|x[i]|^2)
cp.norm(x, 1)    # ∑|x[i]|
cp.norm(x, "inf")    # max {x[i]}
cp.norm(A, "fro")    # Frobenius norm sqrt(∑A[i,j])
cp.norm(A, 1)    # max || A[:,j] ||1
cp.norm(A, "inf")    # max || A[i,:] ||1
cp.norm(A, "nuc")    # nuclear norm tr((A^T*A)^(1/2))
cp.norm(A)    # sqrt(λmax(A^T*A))
cp.pnorm(A, p)    # ||A||p

# polynomial
cp.quad_form(x, A)    # x^T*A*x
