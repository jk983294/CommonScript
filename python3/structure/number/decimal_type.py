from decimal import Decimal
from decimal import localcontext
"""
for arbitrary number precision
"""

a = Decimal('4.2')
b = Decimal('2.1')
print(a + b)  # 6.3
print((a + b) == Decimal('6.3'))  # True

a = Decimal('1.3')
b = Decimal('1.7')
with localcontext() as ctx:
    ctx.prec = 3
    print(a / b)  # 0.765
