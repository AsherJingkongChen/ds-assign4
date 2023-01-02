#include "../../src/graph/graph.hpp"
#include <fstream>

using gh = graph<uint16_t, uint16_t>;

int main() {
  auto count = 100;
  gh::adj_list al;

  for (gh::index_type i = 0; i < count; i++) {
    // al[i + 1] = {{1 + (i + 1) % count, 1}};
    // al[1 + (i + 1) % count] = {{i + 1, 1}};
    al.connect(i + 1, 1 + (i + 1) % count, 1);
  }

  std::ofstream fout_text("test/graph/adjlist.out.log");

  for (auto &p: al) {
    fout_text << p.first << '\n';

    for (auto &q: p.second) {
      fout_text << p.first << ' ' << q << '\n';
    }
  }
}