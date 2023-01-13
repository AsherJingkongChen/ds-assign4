import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv
from math import ceil

# input
#
data = read_csv('output/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
x_min, x_max = 1, 500
y_min, y_max = 1, 500
x_cnt, y_cnt = x_max - x_min + 1, y_max - y_min + 1

x, y = np.meshgrid(
  np.linspace(x_min, x_max, x_cnt),
  np.linspace(y_min, y_max, y_cnt)
)

d = np.reshape(
  data[['D']].transpose().to_numpy(),
  (x_cnt, y_cnt)
).transpose()

# plot
#
fig = plt.figure(figsize=(8, 5))
plt.contourf(x, y, d, cmap='CMRmap')

# label
#
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Mean of shortest distances = D(X, Y)')
plt.colorbar().set_label('D')

# output
#
plt.savefig('output/p_n-1000_x-1-500_y-1-500.png', dpi = 150)

plt.show()
