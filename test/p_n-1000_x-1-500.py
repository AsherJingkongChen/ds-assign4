import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv

# input
#
data = read_csv('output/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
arg = data[data['Y'] == 250].transpose().to_numpy()
x, d = arg[0], arg[2]

# plot
#
fig = plt.figure(figsize=(8, 5))
plt.plot(x, d, color='gray', linewidth=2)

# label
#
plt.xlabel('X')
plt.ylabel('D')
plt.title('Mean of shortest distances = D(X, Y = 250)')

# output
#
plt.savefig('output/p_n-1000_x-1-500.png', dpi = 150)

plt.show()
