#include "../../src/graph/graph.hpp"
#include <fstream>

using namespace graph;
using namespace graph::tag;

using usg_16_16 = simple_graph<uint16_t, uint16_t, undirected>;

int main() {
  usg_16_16::index_type count = 10;

  std::ofstream fout("test/graph/adj_list_100x_cycle.out.log");

  // for (auto &p: al_2) {
  //   fout << p.first << '\n';
  //
  //   for (auto &q: p.second) {
  //     fout << p.first << ' ' << q << '\n';
  //   }
  // }
}