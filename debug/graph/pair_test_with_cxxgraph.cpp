#include "../../src/graph/graph.hpp"
#include "../../third-party/CXXGraph/include/CXXGraph.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <random>
#include <string>

using namespace graph;
using namespace graph::extra::io;

using gh = 
  simple_graph<
    uint16_t, 
    uint16_t, 
    tag::undirected
  >;

using uidist =
  std::uniform_int_distribution<
    gh::length_type
  >;

static std::mt19937 rng(std::random_device{}());

// 1. Generate a cycle of 1000 nodes. Each edge has length 1.
// 2. Add x random edges. Each random edge has the same length y. 
//
int main() {
  gh::index_type  n(1000);
  gh::index_type  x(uidist(1, n * 2)(rng));
  gh::length_type y(uidist(1, n / 2)(rng));

  // for ()
}
