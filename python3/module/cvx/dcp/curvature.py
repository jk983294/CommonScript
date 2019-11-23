import cvxpy as cp
import numpy

# constant      f(x) independent of x
# affine        f(θx+(1−θ)y)=θf(x)+(1−θ)f(y),∀x,y,θ∈[0,1]
# convex        f(θx+(1−θ)y)≤θf(x)+(1−θ)f(y),∀x,y,θ∈[0,1]
# concave       f(θx+(1−θ)y)≥θf(x)+(1−θ)f(y),∀x,y,θ∈[0,1]
# unknown       DCP analysis cannot determine the curvature

x = cp.Variable()
a = cp.Parameter(nonneg=True)

print("curvature of x:", x.curvature)    # AFFINE
print("curvature of a:", a.curvature)    # CONSTANT
print("curvature of square(x):", cp.square(x).curvature)    # CONVEX
print("curvature of sqrt(x):", cp.sqrt(x).curvature)    # CONCAVE
