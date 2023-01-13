import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv
from scipy.ndimage import gaussian_filter1d

# input
#
data = read_csv('output/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
x = (data[['X']].max()[0] + data[['X']].min()[0]) // 2

arg = data[data['X'] == x].to_numpy().transpose()
y, d = arg[1], arg[2]

# plot
#
fig = plt.figure(figsize=(8, 5))
plt.plot(y, d, color='#D0B020', linewidth=1)
plt.plot(y, gaussian_filter1d(d, 20), ':', color='#B09020', linewidth=2)

# label
#
plt.xlabel('Y')
plt.ylabel('D')
plt.title(f'Mean of shortest distances, D(X = {x}, Y)')

# output
#
plt.savefig('output/p_n-1000_y-1-500.png', dpi = 150)

plt.show()
