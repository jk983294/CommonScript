import matplotlib.pyplot as plt

# fig.add_subplot(numrows, numcols, fignum)
fig = plt.figure()
ax1 = fig.add_subplot(2, 1, 1)
ax1.plot([1, 2, 3], [1, 2, 3])
ax2 = fig.add_subplot(2, 1, 2)
ax2.plot([1, 2, 3], [3, 2, 1])
plt.show()
