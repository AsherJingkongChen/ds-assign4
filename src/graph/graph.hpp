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
#include <cstdint>
#include <utility>
#include <functional>
#include <type_traits>
#include <unordered_map>

#if defined __has_include
  #if __has_include (<ext/pb_ds/priority_queue.hpp>)
    #include <ext/pb_ds/priority_queue.hpp>
    #define __HAS_GNU_PBDS_PRIORITY_QUEUE
  #endif
#endif

namespace graph {

namespace tag {

struct _direction_tag {};
struct _algorithm_tag {};

struct undirected: public _direction_tag {};
struct directed: public _direction_tag {};

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE

struct without_decrease_key: public _algorithm_tag {};
struct with_decrease_key: public _algorithm_tag {};

#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

} // namespace tag

// simple_graph<Ip, Lp, Tag>:
//   Ip  - node index type
//   Lp  - edge length type
//   Tag - tag::undirected | tag::directed
//
// as adjacency list: 
//   key s - source node index
//   key t - target node index
//   value - edge length
//
// member types: [TODO]
//   index_type - Ip
//
//   length_type - Lp
//
//   node_list<Tp> - std::unordered_map<Ip, Tp>:
//     key   - node index
//     value - Tp
//
//   length_list - node_list<length_type>
//
//   edge_type - specialized std::tuple<Ip, Ip, Lp>:
//     source - source node index
//     target - target node index
//     length - edge length
//
//   part_edge_type - specialized std::pair<Ip, Lp>:
//     vertex - vertex node index
//     length - edge length
//
//   const_iterator, iterator - forward const_iterator
//
template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
class simple_graph:
  public 
    std::unordered_map<
      _Ip, std::unordered_map<_Ip, _Lp>
    > {

public:
  typedef _Ip index_type;
  typedef _Lp length_type;
  class edge_type;
  class part_edge_type;
  class const_iterator;
  typedef const_iterator iterator;

  template<typename _Tp>
  using node_list      = std::unordered_map<_Ip, _Tp>;

  using part_edge_list = node_list<part_edge_type>;
  using base_type      = node_list<node_list<length_type>>;

public:
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

public:
  // returns an iterator to an existing edge
  // which is linked from source to target or end()
  // if no such edge exists
  //
  const_iterator find(
    index_type const &source, 
    index_type const &target) const;

  // find single source shortest path lengths
  // implementation of Dijkstra's algorithm
  //
  // result type is based on std::unordered_map<Ip, std::pair<Ip, Lp>>
  // each part_edge_type for [target index] is 
  // a pair of predecent index and shortest path length
  //
  // - sssp_lengths(source index),
  // - sssp_lengths< tag::without_decrease_key >(source index):
  //
  //   without decrease key operation
  //   with the help of std::priority_queue (binary heap)
  //
  // - sssp_lengths< tag::with_decrease_key >(source index),
  // - sssp_lengths< tag::with_decrease_key, PqTag >(source index):
  //
  //   with decrease key operation
  //   with the help of __gnu_pbds::priority_queue
  //
  //   PqTag:
  //     one of five __gnu_pbds::priority_queue_tags
  //     which specifies the underlying data structure,
  //     default value is __gnu_pbds::pairing_heap_tag
  //
  // note that in this implementation,
  // initial lengths is std::numeric_limits<Lp>::max()
  //
  part_edge_list
  sssp_lengths(index_type const &source) const
#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE
  {
    return
      sssp_lengths<
        tag::without_decrease_key
      >(source);
  }

  template<
    typename _AlgoTag,
    typename
      std::enable_if<
        std::is_same<
          _AlgoTag, 
          tag::without_decrease_key
        >::value
      >::type* = nullptr
  >
  part_edge_list
  sssp_lengths(index_type const &source) const;

  template<
    typename _AlgoTag,
    typename _PqTag =
      __gnu_pbds::pairing_heap_tag,
    typename
      std::enable_if<
        std::is_same<
          _AlgoTag, 
          tag::with_decrease_key
        >::value
      >::type* = nullptr
  >
  part_edge_list
  sssp_lengths(index_type const &source) const;

#else
;
#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

public:
  // assigns length to an existing edge which is linked
  // from source to target or insert a new edge 
  // if it does not exist
  //
  // returns true if insertion happened or false if assigned
  //
  // if _DirTag is tag::undirected, 
  // the operation in opposite direction will also take place
  //
  std::pair<const_iterator, bool> 
  insert_or_assign(
      index_type const &source, 
      index_type const &target,
      length_type const &length) {
    
    return _insert_or_assign(source, target, length, _DirTag());
  }

private:
  std::pair<const_iterator, bool> 
  _insert_or_assign(
    index_type const &source,
    index_type const &target,
    length_type const &length,
    tag::undirected);

  std::pair<const_iterator, bool> 
  _insert_or_assign(
    index_type const &source,
    index_type const &target,
    length_type const &length,
    tag::directed);

public:
  using base_type::base_type;

  static_assert(
    std::is_unsigned<_Lp>::value, 
    "edge length is currently "
    "only available as unsigned type"
  );
};

} // namespace graph

// definition headers
//
#include "edge_types.hpp"
#include "iterator.hpp"
#include "find.hpp"
#include "insert_or_assign.hpp"
#include "sssp_lengths.hpp"
#include "extra.hpp"

#endif // GRAPH_GRAPH
