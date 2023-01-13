import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv, DataFrame
from math import ceil

# input
#
data = read_csv('output/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
x_bin = data[['X']].max()[0] - data[['X']].min()[0] + 1
y_bin = data[['Y']].max()[0] - data[['Y']].min()[0] + 1

x, y = np.meshgrid(
  np.linspace(
    data[['X']].min()[0],
    data[['X']].max()[0],
    x_bin
  ),
  np.linspace(
    data[['Y']].min()[0],
    data[['Y']].max()[0],
    y_bin
  )
)

d = np.reshape(
  data[['D']].transpose().to_numpy(),
  (
    x_bin,
    y_bin
  )
).transpose()

DataFrame(
  d,
  index = np.linspace(
    data[['Y']].min()[0],
    data[['Y']].max()[0],
    y_bin
  ).astype(np.int32),

  columns = np.linspace(
    data[['X']].min()[0],
    data[['X']].max()[0],
    x_bin
  ).astype(np.int32)

).to_csv('output/d_x_y.csv')

# plot
#
fig = plt.figure(figsize=(8, 5))
plt.contourf(x, y, d, cmap='CMRmap')

# label
#
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Mean of shortest distances, D(X, Y)')
plt.colorbar().set_label('D')


# output
#
plt.savefig('output/p_n-1000_x-1-500_y-1-500.png', dpi = 150)

plt.show()
