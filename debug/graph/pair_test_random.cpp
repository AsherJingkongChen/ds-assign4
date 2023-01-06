// The test file requires Boost Graph Library
//
// References:
//   [BGL Github](https://github.com/boostorg/graph)
//   [Dijkstra's SSSP algorithm example](https://github.com/boostorg/graph/blob/develop/example/dijkstra-example.cpp)
//
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
    graph::tag::undirected
  >;

using uidist =
  std::uniform_int_distribution<
    sg::length_type
  >;

using bg =
  boost::adjacency_list<
    boost::listS, 
    boost::vecS, 
    boost::undirectedS,
    boost::property<boost::vertex_index_t, sg::index_type>,
    boost::property<boost::edge_weight_t, sg::length_type>
  >;

using common_edge_type =
  std::pair<sg::index_type, sg::index_type>;

// 1. generate a cycle of 1000 nodes. Each edge has length 10.
// 2. add x random edges. Each random edge has the same length y.
// 3. use Boost Graph Library and Graph Header Library
//    written in this project to get single source shortest path lengths (SSSP Lengths)
//    with Dijkstra's algorithm, and diff the results
//
// 4. run `number_of_cases` times of operation 1, 2, 3
//
int main() {
  int number_of_cases(500);
  std::ofstream  fout("debug/graph/pair_test_random.cpp.out.log");
  sg::index_type n   (1000);
  auto     seed_const(std::random_device{}());

  fout << "[diff logging begins]\n"
       << "case: seed x y | bg: target parent distance | sg: t. p. d."
       << std::endl;

  for (uint32_t k = number_of_cases; k--;) {
    // [seed]
    //
    auto            seed(k * seed_const);
    std::mt19937_64 rng(seed);
    sg::index_type  x(uidist(1, n / 10)(rng) * 10 * 2);
    sg::length_type y(uidist(1, n / 10 / 2)(rng) * 10);

    // common data build
    //
    std::vector<common_edge_type> relations;
    std::vector<sg::length_type>  weights;

    for (auto i(n); i--;) {
      relations.push_back({i, (i + 1) % n});
      weights.push_back(10);
    }

    for (auto i(x); i--;) {
      relations.push_back({
        uidist(0, n - 1)(rng), 
        uidist(0, n - 1)(rng)
      });
      weights.push_back(y);
    }

    // graph::simple_graph (sg) build
    //
    sg a0;
    for (auto i(weights.size()); i--;) {
      a0.insert_or_assign(
        relations[i].first,
        relations[i].second,
        weights[i]
      );
    }

    auto res = 
      a0.sssp_lengths<
        graph::tag::with_decrease_key,
        __gnu_pbds::binomial_heap_tag
      >(0);

    // boost::adjacency_list (bg) build
    //
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
    auto s(boost::vertex(0, a1));

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

        if (d[*vi] != res[*vi].length()) {
          fout << seed << ' ' << x << ' ' << y << " | "
               << *vi << ' '
               << p[*vi] << ' ' 
               << d[*vi] << " | "
               << *vi << ' '
               << res[*vi].vertex() << ' '
               << res[*vi].length() << '\n';
        }

        // note that different dijkstra practices are possible to
        // have different parent indices for some target indices
        //   ignored: assert(p[*vi] == res[*vi].vertex()); 
        //
    }
  }

  fout << "[diff logging ends]" << std::endl;
}


