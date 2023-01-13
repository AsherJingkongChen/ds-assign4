import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv
from scipy.ndimage import gaussian_filter1d

# input
#
data = read_csv('output/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
y = (data[['Y']].max()[0] + data[['Y']].min()[0]) // 2

arg = data[data['Y'] == y].to_numpy().transpose()
x, d = arg[0], gaussian_filter1d(arg[2], sigma=10)

# plot
#
fig = plt.figure(figsize=(8, 5))

plt.plot(x, d, color = 'gray', linewidth = 2)

# label
#
plt.xlabel('X')
plt.ylabel('D')
plt.title(f'Mean of shortest distances, D(X, Y = {y})')

# output
#
plt.savefig('output/p_n-1000_x-1-500.png', dpi = 150)

plt.show()
