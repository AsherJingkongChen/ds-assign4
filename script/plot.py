#! /usr/bin/env python3
# run this shell script with the command: ./script/plot.py

import numpy as np
import matplotlib.pyplot as plt
from pandas import read_csv, DataFrame
from scipy.ndimage import gaussian_filter1d

# input
#
data_dist = read_csv('output/distances.csv')
data_heap = read_csv('output/heap_time_benchmark.csv')

def xyd():
  # prepare
  #
  x_bin = data_dist[['X']].max()[0] - data_dist[['X']].min()[0] + 1
  y_bin = data_dist[['Y']].max()[0] - data_dist[['Y']].min()[0] + 1

  x, y = np.meshgrid(
    np.linspace(
      data_dist[['X']].min()[0],
      data_dist[['X']].max()[0],
      x_bin
    ),
    np.linspace(
      data_dist[['Y']].min()[0],
      data_dist[['Y']].max()[0],
      y_bin
    )
  )

  d = np.reshape(
    data_dist[['D']].transpose().to_numpy(),
    (
      x_bin,
      y_bin
    )
  ).transpose()

  DataFrame(
    d,
    index = np.linspace(
      y.min(),
      y.max(),
      y_bin
    ).astype(np.int32),

    columns = np.linspace(
      x.min(),
      x.max(),
      x_bin
    ).astype(np.int32)
  ).to_csv('output/x-y-d.csv')

  # plot
  #
  fig = plt.figure(figsize=(8, 6))
  plt.contourf(
    x, y, d,
    cmap = 'CMRmap',
    levels = np.arange(0, data_dist[['D']].max()[0] + 50, 50)
  )
  plt.xlabel('X', loc = 'left')
  plt.ylabel('Y', loc = 'bottom')
  plt.title('Average shortest distances, D(X, Y)')
  plt.colorbar().set_label('D', loc = 'bottom')
  plt.xticks(
    np.arange(0, x.max() + 50, 50)
  )
  plt.yticks(
    np.arange(0, y.max() + 50, 50)
  )

  # output
  #
  plt.savefig('output/x-y-d.png', dpi = 200)

def xd_yd(X, Y):
  # prepare
  #
  arg_x_d = data_dist[data_dist['Y'] == Y].to_numpy().transpose()
  x, x_d = arg_x_d[0], arg_x_d[2]
  arg_y_d = data_dist[data_dist['X'] == X].to_numpy().transpose()
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
    np.arange(0, x.max() + 50, 50)
  )
  plt.yticks(
    np.arange(0, data_dist[['D']].max()[0] + 50, 50)
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
    np.arange(0, y.max() + 50, 50)
  )
  plt.yticks(
    np.arange(0, data_dist[['D']].max()[0] + 50, 50)
  )

  # output
  #
  plt.tight_layout()
  plt.savefig(f'output/x-y{Y}-d_x{X}-y-d.png', dpi = 200)

def fd():
  # prepare
  #
  d = data_dist[['D']].to_numpy().transpose()[0]

  # plot
  # 
  fig = plt.figure(figsize=(8, 6))
  plt.grid(which = 'both', alpha = 0.3)
  plt.hist(d, bins='auto', fc='#B08030', ec='#805000')
  plt.xlabel('D', loc='left')
  plt.ylabel('Frequency', loc='bottom')
  plt.title(f'Average shortest distances distribution, f(D)')
  plt.xticks(
    np.arange(0, d.max() + 50, 50)
  )

  # output
  #
  plt.tight_layout()
  plt.savefig(f'output/f-d.png', dpi = 200)

def heap_benchmark():
  # prepare
  #
  def arg(I):
    res = data_heap[data_heap['I'] == I].to_numpy().transpose()
    return (res[0], res[2])

  x_t_dict = {k: arg(k) for k in [
    'sssp_std_priority_queue',
    'sssp_gnu_pbds_pairing_heap',
    'push_std_priority_queue',
    'push_gnu_pbds_pairing_heap',
    'pop_std_priority_queue',
    'pop_gnu_pbds_pairing_heap'
  ]}

  # plot
  #
  fig = plt.figure(figsize=(8, 6))

  # plot sssp x-t
  #
  fig.add_subplot(311)
  plt.grid(which = 'both', alpha = 0.3)
  plt.plot(
    x_t_dict['sssp_std_priority_queue'][0],
    x_t_dict['sssp_std_priority_queue'][1],
    color = '#60B050',
    linewidth = 1
  )
  plt.plot(
    x_t_dict['sssp_gnu_pbds_pairing_heap'][0],
    x_t_dict['sssp_gnu_pbds_pairing_heap'][1],
    color = '#901010',
    linewidth = 1
  )
  plt.xlabel('X (edge count)', loc = 'left')
  plt.ylabel('T (msec)', loc = 'bottom')
  plt.title(f'Dijkstra\'s SSSP algorithm, time benchmark, T(X)')
  plt.legend(['std_priority_queue', 'gnu_pbds_pairing_heap'])

  # plot push x-t
  #
  fig.add_subplot(312)
  plt.grid(which = 'both', alpha = 0.3)
  plt.plot(
    x_t_dict['push_std_priority_queue'][0],
    x_t_dict['push_std_priority_queue'][1],
    color = '#60B050',
    linewidth = 1
  )
  plt.plot(
    x_t_dict['push_gnu_pbds_pairing_heap'][0],
    x_t_dict['push_gnu_pbds_pairing_heap'][1],
    color = '#901010',
    linewidth = 1
  )
  plt.xlabel('X (pairs of uint32_t)', loc = 'left')
  plt.ylabel('T (msec)', loc = 'bottom')
  plt.title(f'Heap push, time benchmark, T(X)')
  plt.legend(['std_priority_queue', 'gnu_pbds_pairing_heap'])

  # plot pop x-t
  #
  fig.add_subplot(313)
  plt.grid(which = 'both', alpha = 0.3)
  plt.plot(
    x_t_dict['pop_std_priority_queue'][0],
    x_t_dict['pop_std_priority_queue'][1],
    color = '#60B050',
    linewidth = 1
  )
  plt.plot(
    x_t_dict['pop_gnu_pbds_pairing_heap'][0],
    x_t_dict['pop_gnu_pbds_pairing_heap'][1],
    color = '#901010',
    linewidth = 1
  )
  plt.xlabel('X (pairs of uint32_t)', loc = 'left')
  plt.ylabel('T (msec)', loc = 'bottom')
  plt.title(f'Heap pop, time benchmark, T(X)')
  plt.legend(['std_priority_queue', 'gnu_pbds_pairing_heap'])

  # output
  #
  plt.tight_layout()
  plt.savefig(f'output/heap_time_benchmark.png', dpi = 200)

def fd():
  fig = plt.figure(figsize=(8, 6))
  plt.grid(which = 'both', alpha = 0.3)
  plt.hist(
    data_dist[['D']].to_numpy().transpose()[0],
    bins='auto',
    fc='#B08030',
    ec='#805000'
  )
  plt.xlabel('D', loc='left')
  plt.ylabel('Frequency', loc='bottom')
  plt.title(f'Average shortest distances distribution, f(D)')
  plt.xticks(
    np.arange(0, data_dist[['D']].max()[0] + 50, 50)
  )

  # output
  #
  plt.tight_layout()
  plt.savefig(f'output/f-d.png', dpi = 200)


def main():
  xyd()
  xd_yd(5, 5)
  xd_yd(50, 50)
  xd_yd(100, 100)
  xd_yd(200, 200)
  xd_yd(300, 300)
  xd_yd(400, 400)
  heap_benchmark()
  fd()
  # plt.show()

if __name__ == '__main__':
  main()
