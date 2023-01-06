#include "../../src/graph/graph.hpp"
#include <fstream>
#include <cassert>

#undef assert
#define assert(...) void(0)

using namespace graph;
using namespace graph::tag;
using namespace graph::extra::io;

using gh = simple_graph<int32_t, uint32_t, undirected>;

// References:
//   [Dijkstra's algorithm on a undirected graph](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/)
//
int main() {
  gh al_1;

  al_1.insert_or_assign(0, 1, 4);
  al_1.insert_or_assign(0, 7, 8);
  al_1.insert_or_assign(1, 2, 8);
  al_1.insert_or_assign(1, 7, 11);
  al_1.insert_or_assign(2, 3, 7);
  al_1.insert_or_assign(2, 8, 2);
  al_1.insert_or_assign(2, 5, 4);
  al_1.insert_or_assign(3, 4, 9);
  al_1.insert_or_assign(3, 5, 14);
  al_1.insert_or_assign(4, 5, 10);
  al_1.insert_or_assign(5, 6, 2);
  al_1.insert_or_assign(6, 7, 1);
  al_1.insert_or_assign(6, 8, 6);
  al_1.insert_or_assign(7, 8, 7);

  std::ofstream fout("test/graph/shortest_paths_with_dijkstra.out.log");

// general, with or without
// 1 0 4
// 0 0 0
// 7 0 8
// 2 1 12
// 3 2 19
// 8 2 14
// 5 6 11
// 4 5 21
// 6 7 9

// binary, without (?)
// 1 0 4
// 0 0 0
// 7 0 8
// 2 1 12
// 3 2 6 ?
// 8 2 1 ?
// 5 2 3 ?
// 4 3 17 ?
// 6 6 4294967295 ?

  gh::part_edge_list r0 =
    al_1.sssp_lengths<tag::with_decrease_key>(0);

  for (auto &p: r0) {
    fout << p << '\n';
  }

  fout << "edge list:\n";
  for (auto &e: al_1) {
    fout << e << '\n';
  }

// sssp_lengths
  assert(r0[1].length() == 4);
  assert(r0[0].length() == 0);
  assert(r0[7].length() == 8);
  assert(r0[2].length() == 12);
  assert(r0[3].length() == 19);
  assert(r0[8].length() == 14);
  assert(r0[5].length() == 11);
  assert(r0[4].length() == 21);
  assert(r0[6].length() == 9);

// find existing edges
  assert(al_1.find(0, 1) != al_1.end());
  assert(al_1.find(0, 7) != al_1.end());
  assert(al_1.find(1, 2) != al_1.end());
  assert(al_1.find(1, 7) != al_1.end());
  assert(al_1.find(2, 3) != al_1.end());
  assert(al_1.find(2, 8) != al_1.end());
  assert(al_1.find(2, 5) != al_1.end());
  assert(al_1.find(3, 4) != al_1.end());
  assert(al_1.find(3, 5) != al_1.end());
  assert(al_1.find(4, 5) != al_1.end());
  assert(al_1.find(5, 6) != al_1.end());
  assert(al_1.find(6, 7) != al_1.end());
  assert(al_1.find(6, 8) != al_1.end());
  assert(al_1.find(7, 8) != al_1.end());

  assert(al_1.find(1, 0) != al_1.end());
  assert(al_1.find(7, 0) != al_1.end());
  assert(al_1.find(2, 1) != al_1.end());
  assert(al_1.find(7, 1) != al_1.end());
  assert(al_1.find(3, 2) != al_1.end());
  assert(al_1.find(8, 2) != al_1.end());
  assert(al_1.find(5, 2) != al_1.end());
  assert(al_1.find(4, 3) != al_1.end());
  assert(al_1.find(5, 3) != al_1.end());
  assert(al_1.find(5, 4) != al_1.end());
  assert(al_1.find(6, 5) != al_1.end());
  assert(al_1.find(7, 6) != al_1.end());
  assert(al_1.find(8, 6) != al_1.end());
  assert(al_1.find(8, 7) != al_1.end());

// find non-existing edges
  assert(al_1.find(9, 2) == al_1.end());
  assert(al_1.find(7, 4) == al_1.end());
  assert(al_1.find(2, 9) == al_1.end());
  assert(al_1.find(3, 0) == al_1.end());
}
