### formats
Single-precision floating-point float point data:
* sign - 1 bit
* exponent - 8 bits
* mantissa - 23 bits

Double precision number is 64 bit of memory where:
* sign - 1 bit
* exponent - 11 bit
* mantissa - 52 bit

Extended precision is 80 bit numbers where:
* sign - 1 bit
* exponent - 15 bit
* mantissa - 112 bit

### x87 FPU
data transfer instructions:
* FDL - load floating point
* FST - store floating point (in ST(0) register)
* FSTP - store floating point and pop (in ST(0) register)

Arithmetic instructions:
* FADD - add floating point
* FIADD - add integer to floating point
* FSUB - subtract floating point
* FISUB - subtract integer from floating point
* FABS - get absolute value
* FIMUL - multiply integer and floating point
* FIDIV - device integer and floating point

Register
* FPU has eight 10 byte registers organized in a ring stack. Top of the stack - register ST(0), other registers are ST(1), ST(2) … ST(7). 
