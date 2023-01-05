// [GRAPH_Header_Library]
//
#ifndef GRAPH_SSSP_LENGTHS
#define GRAPH_SSSP_LENGTHS

#ifdef __clang__
  #warning GNU C++ Library is required due to the usage of __gnu_pbds::priority_queue
#endif // __clang__

#include <queue>
#include <limits>
#include <ext/pb_ds/priority_queue.hpp>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  typename _AlgoTag,
  typename
    std::enable_if<
      std::is_same<
        _AlgoTag, 
        tag::without_decrease_key
      >::value
    >::type*
>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>
::sssp_lengths(index_type const &source) const {
  part_edge_list r;

  for (auto &e: *this) {
    r[e.source()].length() =
      std::numeric_limits<length_type>::max();
  }

  std::priority_queue<
    part_edge_type,
    std::vector<part_edge_type>,
    std::greater<part_edge_type>
  > q;
  q.push({source, length_type()});

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    if (not (s.length() > r[s.vertex()].length())) {
      r[s.vertex()].length() = s.length();

      for (part_edge_type t: this->at(s.vertex())) {
        if (r[t.vertex()].length() > t.length() + s.length()) {
          r[t.vertex()].length() = (t.length() += s.length());
          r[t.vertex()].vertex() = s.vertex();
          q.push(t);
        }
      }
    }
  }
  return r;
}

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  typename _AlgoTag,
  typename
    std::enable_if<
      std::is_same<
        _AlgoTag, 
        tag::with_decrease_key
      >::value
    >::type*
>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>
::sssp_lengths(index_type const &source) const {
  part_edge_list r;

  for (auto &e: *this) {
    r[e.source()].length() =
      std::numeric_limits<length_type>::max();
  }

  __gnu_pbds::priority_queue<
    part_edge_type,
    std::greater<part_edge_type>,
    __gnu_pbds::pairing_heap_tag
  > q;
  q.push({source, length_type()});

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    if (not (s.length() > r[s.vertex()].length())) {
      r[s.vertex()].length() = s.length();

      for (part_edge_type t: this->at(s.vertex())) {
        if (r[t.vertex()].length() > t.length() + s.length()) {
          r[t.vertex()].length() = (t.length() += s.length());
          r[t.vertex()].vertex() = s.vertex();
          q.push(t);
        }
      }
    }
  }
  return r;
}

} // namespace graph

#endif // GRAPH_SSSP_LENGTHS
