#include "../../src/graph/graph.hpp"
#include <fstream>

using namespace graph;
using namespace graph::tag;
using namespace graph::extra::io;

using usg_16_16 = simple_graph<uint16_t, uint16_t, undirected>;
using dsg_16_32 = simple_graph<uint16_t, uint32_t, directed>;

int main() {
  dsg_16_32::index_type count = 10;
  usg_16_16 al_1;
  dsg_16_32 al_2;

  for (usg_16_16::index_type i = 0; i < count; i++) {
    al_1.insert_or_assign(i + 1, 1 + (i + 1) % count, 1);
  }

  for (dsg_16_32::index_type i = 0; i < count; i++) {
    al_2.insert_or_assign(i + 1, 1 + (i + 1) % count, 100000);
  }

  std::ofstream fout("debug/graph/graphs_which_is_directed_and_not.cpp.out.log");

  fout << "usg_16_16 al_1:\n";

  for (auto &e: al_1) {
    fout << e << '\n';
  }

  fout << "dsg_16_32 al_2:\n";

  for (auto &e: al_2) {
    fout << e << '\n';
  }
}