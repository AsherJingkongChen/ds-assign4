import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from pandas import read_csv

# input
#
data = read_csv('output/d_n-1000_x-1-500_y-1-500.csv').to_numpy()

# prepare
#
x_width = y_width = 500
x, y = np.meshgrid(np.arange(x_width), np.arange(y_width))
z = np.reshape(np.transpose(data)[2], (x_width, y_width))

# plot
#
fig = plt.figure(figsize=(8, 5))
plt.contourf(x, y, z)

# label
#
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Mean of shortest distances = D(X, Y)')
cb = plt.colorbar()
cb.set_label('D')

# output
#
plt.savefig('output/p_n-1000_x-1-500_y-1-500.png', dpi = 150)

plt.show()

