import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv, DataFrame
from scipy.ndimage import gaussian_filter1d

# input
#
data = read_csv('output/distances.csv')

def xyd():
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
  ).to_csv('output/x-y-d.csv')

  # plot
  #
  fig = plt.figure(figsize=(8, 6))
  plt.contourf(
    x, y, d,
    cmap = 'CMRmap',
    levels = np.arange(0, data[['D']].max()[0] + 50, 50)
  )
  plt.xlabel('X', loc = 'left')
  plt.ylabel('Y', loc = 'bottom')
  plt.title('Average shortest distances, D(X, Y)')
  plt.colorbar().set_label('D', loc = 'bottom')
  plt.xticks(
    np.arange(0, data[['X']].max()[0] + 50, 50)
  )
  plt.yticks(
    np.arange(0, data[['Y']].max()[0] + 50, 50)
  )

  # output
  #
  plt.savefig('output/x-y-d.png', dpi = 200)

def xd_yd(X, Y):
  # prepare
  #
  arg_x_d = data[data['Y'] == Y].to_numpy().transpose()
  x, x_d = arg_x_d[0], arg_x_d[2]
  arg_y_d = data[data['X'] == X].to_numpy().transpose()
  y, y_d = arg_y_d[1], arg_y_d[2]

  # plot
  #
  fig = plt.figure(figsize=(8, 6))

  # plot x-d
  #
  fig.add_subplot(211)
  plt.grid(which = 'both', alpha = 0.3)
  plt.plot(x, x_d, color='#D040B0', linewidth=1)
  plt.plot(x, gaussian_filter1d(x_d, 20), ':', color='#A00080', linewidth=1)
  plt.xlabel('X', loc = 'left')
  plt.ylabel('D', loc = 'bottom')
  plt.title(f'Average shortest distances, D(X, Y = {Y})')
  plt.xticks(
    np.arange(0, data[['X']].max()[0] + 50, 50)
  )
  plt.yticks(
    np.arange(0, data[['D']].max()[0] + 50, 50)
  )

  # plot y-d
  #
  fig.add_subplot(212)
  plt.grid(which = 'both', alpha = 0.3)
  plt.plot(y, y_d, color='#D0B040', linewidth=1)
  plt.plot(y, gaussian_filter1d(y_d, 20), ':', color='#A08000', linewidth=1)
  plt.xlabel('Y', loc = 'left')
  plt.ylabel('D', loc = 'bottom')
  plt.title(f'Average shortest distances, D(X = {X}, Y)')
  plt.xticks(
    np.arange(0, data[['Y']].max()[0] + 50, 50)
  )
  plt.yticks(
    np.arange(0, data[['D']].max()[0] + 50, 50)
  )

  # output
  #
  plt.tight_layout()
  plt.savefig(f'output/x-y{Y}-d_x{X}-y-d.png', dpi = 200)

def dq_norm():
  pass

def main():
  xyd()
  xd_yd(50, 50)
  xd_yd(100, 100)
  xd_yd(200, 200)
  xd_yd(300, 300)
  xd_yd(400, 400)
  # plt.show()

if __name__ == '__main__':
  main()
