#include "../../src/graph/graph.hpp"
#include <fstream>
#include <cassert>

using namespace graph;
using namespace graph::tag;

using gh = simple_graph<uint16_t, uint32_t, undirected>;

int main() {
  gh al_1;

  al_1.assign(0, 1, 4);
  al_1.assign(0, 7, 8);
  al_1.assign(1, 2, 8);
  al_1.assign(1, 7, 11);
  al_1.assign(2, 3, 7);
  al_1.assign(2, 8, 2);
  al_1.assign(2, 5, 4);
  al_1.assign(3, 4, 9);
  al_1.assign(3, 5, 14);
  al_1.assign(4, 5, 10);
  al_1.assign(5, 6, 2);
  al_1.assign(6, 7, 1);
  al_1.assign(6, 8, 6);
  al_1.assign(7, 8, 7);

  std::ofstream fout("test/graph/shortest_paths_with_dijkstra.out.log");

  gh::length_list r0 = al_1.sssp_lengths(0);

  for (auto &p: r0) {
    fout << p.first << ' ' << p.second << '\n';
  }

  assert(r0[0] == 0);
  assert(r0[1] == 4);
  assert(r0[2] == 12);
  assert(r0[3] == 19);
  assert(r0[4] == 21);
  assert(r0[5] == 11);
  assert(r0[6] == 9);
  assert(r0[7] == 8);
  assert(r0[8] == 14);

  // for (auto &p: al_2) {
  //   fout << p.first << '\n';
  //
  //   for (auto &q: p.second) {
  //     fout << p.first << ' ' << q << '\n';
  //   }
  // }
}
