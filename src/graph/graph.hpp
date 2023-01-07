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
#include <unordered_map>

#if defined __has_include
  #if __has_include (<ext/pb_ds/priority_queue.hpp>)
    #include <ext/pb_ds/priority_queue.hpp>
    #define __HAS_GNU_PBDS_PRIORITY_QUEUE
  #endif
#endif

#undef enable_if_same_t
#undef enable_if_not_same_t
#undef enable_if_same
#undef enable_if_not_same

#include <type_traits>
#define enable_if_same_t(_Tp, _Up) \
  typename std::enable_if< \
    std::is_same<_Tp, _Up>::value \
  >::type*

#define enable_if_not_same_t(_Tp, _Up) \
  typename std::enable_if< \
    not std::is_same<_Tp, _Up>::value \
  >::type*

#define enable_if_same(_Tp, _Up) \
  typename std::enable_if< \
    std::is_same<_Tp, _Up>::value \
  >::type* = nullptr

#define enable_if_not_same(_Tp, _Up) \
  typename std::enable_if< \
    not std::is_same<_Tp, _Up>::value \
  >::type* = nullptr

namespace graph {

namespace tag {

struct _direction_tag {};
struct undirected: public _direction_tag {};
struct directed: public _direction_tag {};

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE

struct _algorithm_tag {};
struct without_decrease_key: public _algorithm_tag {};
struct with_decrease_key: public _algorithm_tag {};

#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

} // namespace tag

// simple_graph<Ip, Lp, Tag>:
//   Ip     - node index type
//   Lp     - edge length type
//   DirTag - tag::undirected | tag::directed
//
// has an adjacency list: 
//   key s - source node index
//   key t - target node index
//   value - edge length
//
// has two node_lists records vertices indices:
//   sources - node_list<bool>
//   targets - node_list<bool>
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

private:
  node_list<bool> sources;
  node_list<bool> targets;

public:
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // returns an iterator to an existing edge
  // which is linked from source to target or end()
  // if no such edge exists
  //
  const_iterator find(
    index_type const &source, 
    index_type const &target) const;

  // find single source shortest path lengths
  // with Dijkstra's SSSP algorithm
  //
  // result type is based on std::unordered_map<Ip, std::pair<Ip, Lp>>
  // each part_edge_type of [target index]
  // is a std::pair of the index prior to target index (for pathfinding)
  // and the length of shortest path
  //
  // - sssp_lengths(source index),
  // - sssp_lengths< tag::without_decrease_key >(source index):
  //
  //   without decrease key operation
  //   with the help of std::priority_queue (binary heap)
  //   priority queue's initial size is 1
  //
  // - sssp_lengths< tag::with_decrease_key >(source index),
  // - sssp_lengths< tag::with_decrease_key, PqTag >(source index):
  //
  //   with decrease key operation
  //   with the help of __gnu_pbds::priority_queue
  //   priority queue's initial size is number of vertices
  //
  //   PqTag:
  //     one of five __gnu_pbds::priority_queue_tags,
  //     which specifies the underlying data structure
  //
  //     default value is __gnu_pbds::pairing_heap_tag
  //
  //     __gnu_pbds::binary_heap_tag is not available
  //     due to some performance issues
  //
  // note that in this implementation
  // all initial lengths of [target]s is 
  // std::numeric_limits<length_type>::max()
  // but length of [source] is always length_type()
  //
  // note that in a directed graph,
  // a vertex not being the source of all the other vertex
  // will never be pushed into the priority queue 
  //
public:
  part_edge_list
  sssp_lengths(index_type const &source) const {
    return _sssp_lengths_std(source, _DirTag());
  }

public:
  // assigns length to an existing edge which is linked
  // from source to target or 
  // insert a new edge if it does not exist
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

// details

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE
public:
  template<
    typename _AlgoTag,
    enable_if_same(_AlgoTag, tag::without_decrease_key)
  >
  part_edge_list
  sssp_lengths(index_type const &source) const {
    return _sssp_lengths_std(source, _DirTag());
  }

  template<
    typename _AlgoTag,
    typename _PqTag = __gnu_pbds::pairing_heap_tag,
    enable_if_same(_AlgoTag, tag::with_decrease_key)
  >
  part_edge_list
  sssp_lengths(index_type const &source) const {
    return _sssp_lengths_gnu_pbds<_PqTag>(source, _DirTag());
  }
#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

public:
  std::pair<const_iterator, bool> 
  insert_or_assign(edge_type const &edge) {
    return
      _insert_or_assign(
        edge.source(), 
        edge.target(), 
        edge.length(), 
        _DirTag()
      );
  }

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE
private:
  template<
    typename _PqTag = 
      __gnu_pbds::pairing_heap_tag
  >
  part_edge_list
  _sssp_lengths_gnu_pbds(
    index_type const &source,
    tag::undirected) const;

  template<
    typename _PqTag = 
      __gnu_pbds::pairing_heap_tag
  >
  part_edge_list
  _sssp_lengths_gnu_pbds(
    index_type const &source,
    tag::directed) const;

#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

private:
  part_edge_list
  _sssp_lengths_std(
    index_type const &source,
    tag::undirected) const;

  part_edge_list
  _sssp_lengths_std(
    index_type const &source,
    tag::directed) const;

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

  std::pair<const_iterator, bool> 
  _insert_or_assign(
    index_type const &source,
    index_type const &target,
    length_type const &length);

public:
  using base_type::base_type;

  static_assert(
    std::is_unsigned<_Lp>::value, 
    "edge length is currently "
    "only available as unsigned type for the sake of "
    "Dijkstra's SSSP algorithm"
  );
};

} // namespace graph

// definition headers
//
#include "extra.hpp"
#include "edge_types.hpp"
#include "iterator.hpp"
#include "find.hpp"
#include "insert_or_assign.hpp"
#include "sssp_lengths.hpp"

#undef enable_if_same_t
#undef enable_if_not_same_t
#undef enable_if_same
#undef enable_if_not_same

#endif // GRAPH_GRAPH
