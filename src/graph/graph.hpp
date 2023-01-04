// [GRAPH_Header_Library]
//
// MIT License
//
// Copyright (C) 2023 Asher Chen
// 
// Permission is hereby granted, free of charge, 
// to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), 
// to deal in the Software without restriction, 
// including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and 
// this permission notice shall be included 
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", 
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
// THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// References:
//   [std::unordered_map](https://gcc.gnu.org/onlinedocs/gcc-12.2.0/libstdc++/api/a08926.html)
//   [std::priority_queue](https://gcc.gnu.org/onlinedocs/gcc-12.2.0/libstdc++/api/a08762.html)
//   [Dijkstra's algorithm with and without decrease key](https://www3.cs.stonybrook.edu/~rezaul/papers/TR-07-54.pdf)
//   [Dijkstra's algorithm introduction](http://nmamano.com/blog/dijkstra/dijkstra.html)
//
#ifndef GRAPH_GRAPH
#define GRAPH_GRAPH

#include <tuple>
#include <vector>
#include <cstdint>
#include <utility>
#include <functional>
#include <type_traits>
#include <unordered_map>

namespace graph {

namespace tag {

struct undirected {};
struct directed {};

} // namespace tag

// simple_graph<Ip, Lp, Tag>:
//   Ip  - node index type
//   Lp  - edge length type
//   Tag - tag::undirected | tag::directed
//
// using adjacency list: 
//   key 1 - start node index
//   key 2 - end node index
//   value - edge length
//
// member types:
//   1. index_type - Ip
//   2. length_type - Lp
//   3. node_list<value_type>:
//     key   - node index
//     value - custom value type
//   4. edge_list:
//     get<0> - start node index
//     get<1> - end node index
//     get<2> - edge length
//   5. length_list - node_list<length_type>
//
template<
  typename _Ip,
  typename _Lp,
  typename _Tag
>
class simple_graph:
  public 
    std::unordered_map<
      _Ip, std::unordered_map<_Ip, _Lp>
    > {

public:
  typedef _Ip index_type;
  typedef _Lp length_type;

  // node list:
  //   key   - node index
  //   value - custom value type
  //
  template<typename value_type>
  using node_list = 
    std::unordered_map<_Ip, value_type>;

  // edge_list:
  //   get<0> - start node index
  //   get<1> - end node index
  //   get<2> - edge length
  //
  using edge_list =
    std::vector<std::tuple<_Ip, _Ip, _Lp>>;

  typedef node_list<_Lp> length_list;

public:
  // copy all edges into an edge list
  //
  edge_list edges() const;

public:
  // assign length to an edge which is linked
  // from start to end in-place
  //
  // usage:
  //   simple_graph<> sug;
  //   sug.assign(3, 7, 4);
  //   sug[3][7] == sug[7][3] == 4; // true
  //   sug[3][7] = 10;
  //   sug[3][7] == 10; // true
  //   sug[7][3] == 10; // false
  //
  void assign(
      index_type start, 
      index_type end,
      length_type length) {

    assign(start, end, length, _Tag());
  }

  // find single source shortest path lengths
  // using Dijkstra's algorithm without decrease key
  // using std::priority_queue (binary heap)
  //
  length_list
  sssp_lengths(index_type source) const;

  // find single source shortest paths
  // using Dijkstra's algorithm with decrease key
  // using __gnu_pbds::::priority_queue (pairing heap)
  //
  // length_list
  // sssp_lengths(index_type source) const;

private:
  void assign(_Ip, _Ip, _Lp, tag::undirected);
  void assign(_Ip, _Ip, _Lp, tag::directed);

public:
  using
    std::unordered_map<
      _Ip, std::unordered_map<_Ip, _Lp>
    >
    ::unordered_map;

  static_assert(
    std::is_unsigned<_Lp>::value, 
    "edge length is currently "
    "only available as unsigned type"
  );
};

} // namespace graph

// definition headers
//
#include "edges.hpp"
#include "assign.hpp"
#include "sssp_lengths.hpp"

#endif // GRAPH_GRAPH
