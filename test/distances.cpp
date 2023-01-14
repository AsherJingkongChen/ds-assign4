#include "../src/graph/graph.hpp"
#include "../src/math/math.hpp"

#define RNG_SEED 14641

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <random>

using namespace graph::extra::io;

using us_graph =
  graph::simple_graph<
    uint32_t,
    uint32_t,
    graph::tag::undirected
  >;

using idx_t     = us_graph::index_type;
using len_t     = us_graph::length_type;

template<typename _IntTp>
using dist = std::uniform_int_distribution<_IntTp>;

int main(int argc, const char* argv[]) {
  std::ofstream
  fout_csv(
    "output/distances.csv"
  );
  fout_csv << "X,Y,D\n";

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
  const idx_t  N   (1000);
  const idx_t  X_M (500);
  const len_t  Y_M (500);
  const idx_t  X_m (1);
  const len_t  Y_m (1);
  const idx_t  Z   (50);

  for (auto X(X_m); X <= X_M; X++) {
    for (auto Y(Y_m); Y <= Y_M; Y++) {
      us_graph g;

      // build g, an undirected graph
      // with 1000 vertices and 1000 + X edges
      //
      for (auto i(N); i--;) {
        g.insert(i, (i + 1) % N, 1);
      }

      for (auto i(X); i--;) {
        auto src = dist<idx_t>(0, N - 1)(rng);
        auto tar = dist<idx_t>(0, N - 1)(rng);

        if (not g.insert(src, tar, Y).second) {
          i++; continue;
        }
      }

      // sample Z edges randomly
      //
      len_t D_Z(0);
      for (auto i(Z); i--;) {
        auto r =
          g.sssp<graph::tag::std_priority_queue>(
            std::next(
              g.sources().begin(),
              dist<idx_t>(0, g.sources().size() - 1)(rng)
            )
            ->first
          );

        if (r.empty()) {
          i++; continue;
        }

        D_Z +=
          std::next(
            r.begin(),
            dist<idx_t>(0, r.size() - 1)(rng)
          )
          ->second.length();
      }

      // output as csv file
      //
      float D(D_Z / float(Z));

      fout_csv << X << ','
               << Y << ','
               << D << '\n';
    }
  }
}

// [NOTE]
// - N = 1000
// - Z = 50
// - all 1000 nodes has an index in [0, 999]
// - X + 1000 edges are added
// - X edges are added randomly
// - Z edges are sampled randomly
//
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