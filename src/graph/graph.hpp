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

#include <queue>
#include <limits>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include "enable_if.hpp"

#if defined __has_include
  #if __has_include (<ext/pb_ds/priority_queue.hpp>)
    #include <ext/pb_ds/priority_queue.hpp>
    #define __HAS_GNU_PBDS_PRIORITY_QUEUE
  #endif
#endif

namespace graph {

namespace tag {

struct undirected {};
struct directed {};

struct std_priority_queue {};

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE

typedef __gnu_pbds::binary_heap_tag       binary_heap;
typedef __gnu_pbds::binomial_heap_tag     binomial_heap;
typedef __gnu_pbds::pairing_heap_tag      pairing_heap;
typedef __gnu_pbds::rc_binomial_heap_tag  rc_binomial_heap;
typedef __gnu_pbds::thin_heap_tag         thin_heap;

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
// member types:
//   index_type - Ip
//
//   length_type - Lp
//
//   edge_type - specialized std::tuple<Ip, Ip, Lp>:
//     source - source node index
//     target - target node index
//     length - edge length
//     lexicographically comparable
//
//   part_edge_type - specialized std::pair<Ip, Lp>:
//     vertex - index_type
//     length - edge length
//     lexicographically comparable
//
//   const_iterator, iterator - forward const_iterator
//
//   node_list<Tp> - std::unordered_map<Ip, Tp>:
//     key   - node index
//     value - Tp
//
//   part_edge_list = node_list<part_edge_type>:
//     key   - index_type
//     value - part_edge_type
//
template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
class simple_graph:
  private 
    std::unordered_map<
      _Ip, std::unordered_map<_Ip, _Lp>
    > {

public:
  typedef _Ip             index_type;
  typedef _Lp             length_type;
  class                   edge_type;
  class                   part_edge_type;
  class                   const_iterator;
  typedef const_iterator  iterator;

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
public:
  const_iterator find(
    index_type const &source, 
    index_type const &target) const;

  // find `Single Source Shortest Paths`
  // with Dijkstra's algorithm
  //
  // result type is based on std::unordered_map<Ip, std::pair<Ip, Lp>>
  // each part_edge_type of [target index]
  // is a std::pair of the index prior to target index (for pathfinding)
  // and the length of shortest path
  //
  // - sssp(source index),
  // - sssp< LengthMax >(source index),
  // - sssp< PqTag, [LengthMax] >(source index):
  //
  //   PqTag:
  //     specifying the underlying data structure and algorithms
  //
  //     graph::tag::std_priority_queue - using std::priority_queue
  //     graph::tag::binary_heap        - using __gnu_pbds::priority_queue with binary_heap_tag
  //     graph::tag::binomial_heap      - using __gnu_pbds::priority_queue with binomial_heap_tag
  //     graph::tag::pairing_heap       - using __gnu_pbds::priority_queue with pairing_heap_tag
  //     graph::tag::rc_binomial_heap   - using __gnu_pbds::priority_queue with rc_binomial_heap_tag
  //     graph::tag::thin_heap          - using __gnu_pbds::priority_queue with thin_heap_tag
  //
  //     default value is graph::tag::std_priority_queue
  //
  //     __gnu_pbds::binary_heap_tag is not available
  //     due to some performance issues [TODO]
  //
  // note that in this implementation
  // all initial lengths of [target]s is by default
  // std::numeric_limits<length_type>::max() or custom 
  // but length of [source] is always length_type()
  //
public:
  part_edge_list sssp(index_type const &source) const {
    return
      _sssp_sfinae<
        tag::std_priority_queue,
        std::numeric_limits<length_type>::max()
      >(source);
  }

  template<_Lp _LengthMax>
  part_edge_list sssp(index_type const &source) const {
    return
      _sssp_sfinae<
        tag::std_priority_queue,
        _LengthMax
      >(source);
  }

  template<
    typename _PqTag,
    _Lp _LengthMax = std::numeric_limits<_Lp>::max()
  >
  part_edge_list sssp(index_type const &source) const {
    return _sssp_sfinae<_PqTag, _LengthMax>(source);
  }

public:
  // assigns length to an existing edge which is linked
  // from source to target or 
  // insert a new edge if it does not exist
  //
  // returns true if insertion happened or false if assigned
  //
  // if _DirTag is tag::undirected, 
  // this operation in opposite direction will also take place
  //
  std::pair<const_iterator, bool> 
  insert_or_assign(
      index_type const &source, 
      index_type const &target,
      length_type const &length) {
    
    return _insert_or_assign(source, target, length, _DirTag());
  }

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

// helper methods
//
private:
  template<
    typename _PqTag,
    _Lp _LengthMax,
    typename =
      enable_if_same<_PqTag, tag::std_priority_queue>
  >
  part_edge_list _sssp_sfinae(index_type const &source) const {
    return
      _sssp<
        std::priority_queue<
          part_edge_type,
          std::vector<part_edge_type>,
          std::greater<part_edge_type>
        >,
        _LengthMax
      >(source);
  }

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE
private:
  template<
    typename _PqTag,
    _Lp _LengthMax,
    typename =
      enable_if_not_same<_PqTag, tag::std_priority_queue>,
    typename =
      enable_if_convertible<
        _PqTag,
        __gnu_pbds::priority_queue_tag
      >
  >
  part_edge_list _sssp_sfinae(index_type const &source) const {
    return
      _sssp<
        __gnu_pbds::priority_queue<
          part_edge_type,
          std::greater<part_edge_type>,
          _PqTag
        >,
        _LengthMax
      >(source);
  }
#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

private:
  template<
    typename _PriorityQueue,
    _Lp _LengthMax
  >
  part_edge_list
  _sssp(index_type const &source) const;

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

  static_assert(std::is_unsigned<_Lp>::value,
    "length_type (edge weight data type) is currently "
    "only available as unsigned type for the sake of "
    "Dijkstra's single source shortest paths algorithm"
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
#include "sssp.hpp"

#endif // GRAPH_GRAPH
