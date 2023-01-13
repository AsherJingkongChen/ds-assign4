import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import pandas as pd

# input
#
data = pd.read_csv('private/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
x_min, x_max = 1, 500
y_min, y_max = 1, 500
x_cnt, y_cnt = x_max - x_min + 1, y_max - y_min + 1
d_cnt = 20

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
plt.contourf(x, y, d, cmap='twilight', levels = np.linspace(0, 500, d_cnt + 1))

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
