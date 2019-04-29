#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * what --ffast-math do
 * 1. -funsafe-math-optimizations -fassociative-math it does break strict IEEE compliance, allowing e.g. the reordering
 * of instructions to something which is mathematically the same (ideally) but not exactly the same in floating point.
 * 2. -fno-math-errno it disables setting errno after single-instruction math functions, which means avoiding a write to
 * a thread-local variable (this can make a 100% difference for those functions on some architectures).
 * 3. -ffinite-math-only it makes the assumption that all math is finite, which means that no checks for NaN (or zero)
 * are made in place where they would have detrimental effects. It is simply assumed that this isn't going to happen.
 * 4. -freciprocal-math it enables reciprocal approximations for division and reciprocal square root.
 * 5. -fno-rounding-math -fno-signed-zeros it disables signed zero (code assumes signed zero does not exist, even if the
 * target supports it) and rounding math, which enables among other things constant folding at compile-time.
 * 6. -fno-signaling-nans -fno-trapping-math it generates code that assumes that no hardware interrupts can happen due
 * to signalling/trapping math (that is, if these cannot be disabled on the target architecture and consequently do
 * happen, they will not be handled).
 */

int main() {
    float infinity = INFINITY;        // 1.0 / 0.0
    float nega_infinity = -INFINITY;  // log (0.0)
    float nan = NAN;                  // sqrt(-1.0)
    return 0;
}
