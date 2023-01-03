#include "../../src/graph/graph.hpp"
#include <fstream>

using namespace graph;
using namespace graph::tag;

using usg_16_16 = simple_graph<uint16_t, uint16_t, undirected>;
using dsg_32_32 = simple_graph<uint32_t, uint32_t, directed>;

int main() {
  dsg_32_32::index_type count = 10;
  usg_16_16 al_1;
  dsg_32_32 al_2;

  for (usg_16_16::index_type i = 0; i < count; i++) {
    al_1.emplace(i + 1, 1 + (i + 1) % count, 1);
  }

  for (dsg_32_32::index_type i = 0; i < count; i++) {
    al_2.emplace(i + 1, 1 + (i + 1) % count, 100000);
  }

  std::ofstream fout("test/graph/2_adj_list_cycle.cpp.out.log");

  fout << "usg_16_16 al_1:\n";

  for (auto &p: al_1) {
    fout << p.first << '\n';

    for (auto &q: p.second) {
      fout << p.first << ' ' << q << '\n';
    }
  }

  fout << "dsg_32_32 al_2:\n";

  for (auto &p: al_2) {
    fout << p.first << '\n';

    for (auto &q: p.second) {
      fout << p.first << ' ' << q << '\n';
    }
  }
}