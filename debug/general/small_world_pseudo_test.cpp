#include "../../src/graph/graph.hpp"
#include "../../src/tool/tool.hpp"
#include "../../src/math/math.hpp"
#include "../../src/xml/xml.hpp"

// #define RNG_SEED 

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <random>

using namespace graph::extra::io;

using us_graph =
  graph::simple_graph<
    uint16_t,
    uint64_t,
    graph::tag::undirected
  >;

using cnt_t     = std::size_t;
using idx_t     = us_graph::index_type;
using len_t     = us_graph::length_type;
using vec2      = math::vec2;
using vec2_list = us_graph::node_list<vec2>;

template<typename _IntTp>
using dist = std::uniform_int_distribution<_IntTp>;

int main(int argc, const char* argv[]) {
  std::ofstream fout("debug/general/small_world_pseudo_test.cpp.out.log");

  // parameters and structures
  //
  const std::mt19937::result_type
  SEED (
#ifdef RNG_SEED
    RNG_SEED
#else
    std::random_device{}()
#endif // RNG_SEED
  );
  std::mt19937 rng (SEED);
  const cnt_t  N   (10);
  const cnt_t  X   (
    dist<cnt_t>{0, math::binom_coef(N, cnt_t(2)) - N}(rng)
  );
  const len_t  Y   (
    dist<len_t>{1, N / 2 - 1}(rng)
  );

  const float  R_WH(2);
  const float  W   (N * R_WH);
  const float  H   (N);
  const vec2   C   (W / 2, H / 2);

  // const auto stroke_width = 0.1F; [TODO]
  // root->fill = "white";

  us_graph     g;
  vec2_list    s;

  // build an undirected graph
  //
  for (auto i(N); i--;) {
    g.insert_or_assign(i, (i + 1) % N, 1);
    s[i] = C + math::polar();
  }

  for (auto i(X); i--;) {
    g.insert_or_assign(
      dist<idx_t>{0, N - 1}(rng),
      dist<idx_t>{0, N - 1}(rng),
      Y
    );
  }

  // debug [TODO]
  //
  fout << SEED << " (SEED)\n";
  for (auto &e: g) {
    fout << e << '\n';
  }

  static_assert(N > 2,
    "N should be greater than or equal to 2"
  );
}

// [SPECIFICATION]
//
// # Study the Properties of "Small World" and Compare Different Data Structures
// 
// *Due: 1/17 23:59:59*
// 
// 1. Generate a cycle of 1000 nodes. Each edge has length 1.
// 2. Add X random edges. Each random edge has the same length Y. 
// 3. Sample Z pairs of source and destination, and compute the average shortest distance (D) of these Z source-destination pairs.
// 
// You need to use 2 different structures of heaps. **(In the report, give the name of the data structures that you use, e.g., array and binomial heap).**
// 
// **Your report should contain:**
// 
// 1. A picture of the graph with X = 100.
// 2. Responses to the following questions: 
//     - What is the relationship between X and D? 
//     - What is the relationship between Y and D?
//     - How to choose Z to obtain a reasonable approximation of the true average shortest distance between all pairs of source and destination?
//     - Which implementation of Dijkstra's Algorithm is faster?
// 
// **You need to support your answers with experimental results.** 
// **You also need to explain how you obtain the results.**
//
// [NOTE]
// all nodes has an index in [0, 999]
// the range of X is [0, nCk(1000, 2) - 1000]
// the range of Y is [1, 499]
//