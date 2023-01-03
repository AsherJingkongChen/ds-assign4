#include "../../src/graph/graph.hpp"
#include <fstream>

using namespace graph;
using namespace graph::tag;

using usg_16_32 = simple_graph<uint16_t, uint32_t, undirected>;

int main() {
  usg_16_32::index_type count = 10;
  usg_16_32 al_1;

  for (usg_16_32::index_type i = 0; i < count; i++) {
    al_1.assign(i + 1, 1 + (i + 1) % count, 1);
  }

  std::ofstream fout("test/graph/shortest_paths_with_dijkstra.out.log");

  for (auto &p: al_1.shortest_paths(1)) {
    fout << p.first << ' ' << p.second << '\n';
  }

  // for (auto &p: al_2) {
  //   fout << p.first << '\n';
  //
  //   for (auto &q: p.second) {
  //     fout << p.first << ' ' << q << '\n';
  //   }
  // }
}