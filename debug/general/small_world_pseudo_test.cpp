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

using cnt_t = std::size_t;
using idx_t = undirected_graph::index_type;
using len_t = undirected_graph::length_type;

template<typename _IntTp>
using dist = std::uniform_int_distribution<_IntTp>;

int main(int argc, const char* argv[]) {
  const std::mt19937::result_type
  seed (
#ifdef RNG_SEED
    RNG_SEED
#else
    std::random_device{}()
#endif // RNG_SEED
  );

  std::mt19937 rng (seed);
  const cnt_t  n   (1000);
  const cnt_t  x   (dist<cnt_t>{1, math::binom_coef(n, 2) - n}(rng));
  const len_t  y   (dist<len_t>{1, n / 2 - 1}(rng));
  us_graph     g;

  // vertex index range is [0, 999]
  //
  for (auto i(n); i--;) {
    g.insert_or_assign(
      i, (i + 1)
    );
  }
}

// [APPENDIX]
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
