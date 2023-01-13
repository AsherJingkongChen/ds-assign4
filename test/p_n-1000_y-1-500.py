import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from pandas import read_csv

# input
#
data = read_csv('private/d_n-1000_x-1-500_y-1-500.csv')

# prepare
#
arg = data[data['X'] == 250].transpose().to_numpy()
y, d = arg[1], arg[2]

# plot
#
fig = plt.figure(figsize=(8, 5))
plt.plot(y, d, color='gray', linewidth=2)

# label
#
plt.xlabel('Y')
plt.ylabel('D')
plt.title('Mean of shortest distances = D(X = 250, Y)')

# output
#
plt.savefig('output/p_n-1000_y-1-500.png', dpi = 150)

plt.show()
