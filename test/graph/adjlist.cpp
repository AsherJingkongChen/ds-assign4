#include "../../src/graph/graph.hpp"
#include <fstream>

int main() {
  graph::adjacent_list adjl;
  auto count = 100;
  for (graph::index_type i = 0; i < count; i++) {
    adjl[i + 1] = {{i + 1, 1 + (i + 1) % count}};
  }

  std::ofstream fout_text("test/graph/adjlist.out.log");

  for (auto &p: adjl) {
    fout_text << p.first << '\n';

    for (auto &q: p.second) {
      fout_text << q;
    }
  }
}