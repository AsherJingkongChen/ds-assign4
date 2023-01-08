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

using undirected_graph =
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


}