import matplotlib.pyplot as plt
import numpy as np

# color
# b     blue
# c     cyan
# g     green
# k     black
# m     magenta
# r     red
# w     white
# y     yellow

# line style
# -     solid line
# --    dashed line
# -.    dash-dot line
# :     dotted line

# marker
# .     Point Point
# ,     Pixel Point
# o     Circle marker
# v     Triangle down marker
# ^     Triangle up marker
# <     Triangle left marker
# >     Triangle right marker
# 1     Tripod down marker
# 2     Tripod up marker
# 3     Tripod left marker
# 4     Tripod right marker
# s     Square marker
# p     Pentagon marker
# *     Star marker
# h     Hexagon marker
# H     Rotated hexagon marker
# +     Plus marker
# x     Cross (x) marker
# D     Diamond marker
# d     Thin diamond marker
# |     Vertical line marker
# _     Horizontal line marker

# keywords
# color             Sets the color of the line
# linestyle         Sets the color of the line
# linewidth         Sets the line width
# marker            Sets the line marker style
# markeredgecolor   Sets the marker edge color
# markeredgewidth   Sets the marker edge width
# markerfacecolor   Sets the marker face color
# markersize        Sets the marker size in points

y = np.arange(1, 3, 0.3)
# color / marker / line style
plt.plot(y, 'cx--', y + 1, 'mo:', y + 2, 'kp-.')

plt.plot(y + 3, color='blue', linestyle='dashdot', linewidth=4, marker='o', markerfacecolor='red',
         markeredgecolor='black', markeredgewidth=3, markersize=12)

plt.xticks(range(1, 8, 2))
plt.yticks(range(1, 8, 2))
plt.savefig('line_decoration.png')
plt.show()
