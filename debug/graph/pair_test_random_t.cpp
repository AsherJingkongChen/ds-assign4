// The test file requires Boost Graph Library
//
// References:
//   [BGL Github](https://github.com/boostorg/graph)
//   [BGL Dijkstra's SSSP algorithm example](https://github.com/boostorg/graph/blob/develop/example/dijkstra-example.cpp)
//
#include "def_pair_test_random.hpp"
#define PQTAG graph::tag::thin_heap

#include "../../src/graph/graph.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <random>
#include <string>

#if defined __has_include
  #if __has_include (<boost/graph/graph_traits.hpp>)
    #include <boost/graph/graph_traits.hpp>
    #include <boost/graph/adjacency_list.hpp>
    #include <boost/graph/dijkstra_shortest_paths.hpp>
    #define __HAS_BGL
  #endif
#endif

#ifndef __HAS_BGL
  #warning Boost Graph Library is not found, this test will fail to compile
#endif // __HAS_BGL

using namespace graph::extra::io;

using sg =
  graph::simple_graph<
    uint16_t, 
    uint32_t,
#if __IS_DIRECTED
    graph::tag::directed
#else
    graph::tag::undirected
#endif
  >;

using bg =
  boost::adjacency_list<
    boost::listS, 
    boost::vecS,
#if __IS_DIRECTED
    boost::directedS,
#else
    boost::undirectedS,
#endif
    boost::property<boost::vertex_index_t, sg::index_type>,
    boost::property<boost::edge_weight_t, sg::length_type>
  >;

using uidist =
  std::uniform_int_distribution<sg::length_type>;

// 1. generate 1000 edges between two random vertices whose indices
//    are ranged from 0 until 999, and each edge has length 10
//
// 2. add x random edges with random length y
//    x is [1, 5000], y is [1, 10]
//
// 3. use Boost Graph Library and Graph Header Library
//    written in this project to get
//    single source shortest path lengths from random index v
//    with Dijkstra's algorithm, and diff the results
//
// 4. run `number_of_cases` times of operation 1, 2, 3
//
int main() {
  int number_of_cases(200);
  std::ofstream  fout("debug/graph/pair_test_random_t.log");
  auto     seed_const(std::random_device{}());

  fout << "[diff logging begins]\n"
       << "case: seed x v | bg: target parent distance | sg: t. p. d."
       << std::endl;

  bool fout_triggered = false;

  for (uint32_t k = number_of_cases; k--;) {
    // [seed]
    //
    auto            seed(k * seed_const);
    std::mt19937    rng(seed);
    sg::index_type  n(1000);
    sg::index_type  x(uidist(1, 5000)(rng));
    sg::index_type  v(uidist(0, n - 1)(rng));

    // graph::simple_graph (sg) build
    //
    sg a0;
    for (auto i(n); i--;) {
      a0.insert_or_assign(
        uidist(0, n - 1)(rng),
        uidist(0, n - 1)(rng),
        n / 100
      );
    }

    for (auto i(x); i--;) {
      sg::length_type y(uidist(1, std::max(n / 100, 1))(rng));

      a0.insert_or_assign(
        uidist(0, n - 1)(rng), 
        uidist(0, n - 1)(rng),
        y
      );
    }

    // [ALGORITHMS]
    //
    auto res = a0.sssp<PQTAG>(v);

    // boost::adjacency_list (bg) build
    //
    std::vector<
      std::pair<sg::index_type, sg::index_type>
    > relations;

    std::vector<sg::length_type> weights;

    for (auto &e: a0) {
      relations.push_back({
        e.source(),
        e.target()
      });

      weights.push_back(e.length());
    }

    bg a1(
      relations.begin(),
      relations.end(),
      weights.begin(),
      n
    );

    std::vector<
      boost::graph_traits<bg>::vertex_descriptor
    > p(boost::num_vertices(a1));

    std::vector<sg::length_type> d(boost::num_vertices(a1));
    auto s(boost::vertex(v, a1));

    boost::dijkstra_shortest_paths(
      a1, s,
      boost::predecessor_map(
        boost::make_iterator_property_map(
          p.begin(), boost::get(boost::vertex_index, a1)
        ))
      .distance_map(
        boost::make_iterator_property_map(
          d.begin(), boost::get(boost::vertex_index, a1)
        )
      )
    );

    boost::graph_traits<bg>::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = boost::vertices(a1);
         vi != vend; ++vi) {

      if (res.find(*vi) == res.end()) {
        if (not __IS_DIFF_MODE) {

          fout_triggered = true;
    
          fout  << seed << ' ' << x << ' ' << v << " | "
                << *vi << ' '
                << p[*vi] << ' ' 
                << d[*vi] << " |\n";
        }

      } else if (not __IS_DIFF_MODE ||
                 d[*vi] != res[*vi].length()) {

        fout_triggered = true;

        fout  << seed << ' ' << x << ' ' << v << " | "
              << *vi << ' '
              << p[*vi] << ' ' 
              << d[*vi] << " | "
              << *vi << ' '
              << res[*vi].vertex() << ' '
              << res[*vi].length() << '\n';
      }

      // note that different dijkstra practices are possible to
      // have different parent indices for some target indices
      // so that's why the assertion 
      // for (p[*vi] == res[*vi].vertex()) is ignored
    }

    if (fout_triggered) {
      fout << "\nedge:\n";
      for (auto &e: a0) {
        fout << e << "\n";
      }
      fout << "\ntpd:\n";
      for (auto &tpd: res) {
        fout << tpd << "\n";
      }
      fout << "^[" << k << "]\n\n";
    }
  }

  fout << "[diff logging ends]" << std::endl;

  assert(not fout_triggered);
}
