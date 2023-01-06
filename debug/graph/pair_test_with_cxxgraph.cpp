#include "../../src/graph/graph.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <random>
#include <string>

// References:
//   [CXXGraph](https://github.com/ZigRazor/CXXGraph)
//   [CXXGraph Release v0.4.0](https://github.com/ZigRazor/CXXGraph/releases/tag/v0.4.0)
//
// note that CXXGraph also requires the OpenSSL library
//
#if defined __has_include
  #if __has_include (<openssl/sha.h>)
    #include "../../third-party/CXXGraph/include/CXXGraph.hpp"
    #define __has_openssl_sha
  #endif
#endif

#ifndef __has_openssl_sha
  #warning CXXGraph requires the OpenSSL library.
  #warning if there are no available OpenSSL headers, CXXGraph will not be included.
#endif // __has_openssl_sha

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

// 1. Generate a cycle of 1000 nodes. Each edge has length 1.
// 2. Add x random edges. Each random edge has the same length y. 
//
int main() {
  std::mt19937    rng(std::random_device{}());
  gh::index_type  n(1000);
  gh::index_type  x(uidist(1, n * 2)(rng));
  gh::length_type y(uidist(1, n / 2)(rng));

  // for ()
}
