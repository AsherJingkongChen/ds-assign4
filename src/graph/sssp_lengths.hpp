// [GRAPH_Header_Library]
//
#ifndef GRAPH_SSSP_LENGTHS
#define GRAPH_SSSP_LENGTHS

#ifdef __clang__
  #warning GNU C++ Library is required due to the usage of __gnu_pbds::priority_queue
#endif // __clang__

#include <limits>
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>

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
  using priority_queue = 
    __gnu_pbds::priority_queue<
      part_edge_type,
      std::greater<part_edge_type>,
      __gnu_pbds::binary_heap_tag
    >;

  part_edge_list r;

  for (auto &p: static_cast<base_type const &>(*this)) {
    r[p.first] = {
      p.first,
      std::numeric_limits<length_type>::max()
    };
  }

  r[source].length() = length_type();

  priority_queue q;
  q.push({source, r[source].length()});

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    for (part_edge_type t: this->at(s.vertex())) {
      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};
        q.push(t);
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
  using priority_queue = 
    __gnu_pbds::priority_queue<
      part_edge_type,
      std::greater<part_edge_type>,
      __gnu_pbds::binomial_heap_tag
    >;

  part_edge_list r;
  node_list<typename priority_queue::point_iterator> h;

  for (auto &p: static_cast<base_type const &>(*this)) {
    r[p.first] = {
      p.first,
      std::numeric_limits<length_type>::max()
    };
  }

  r[source].length() = length_type();

  priority_queue q;
  for (auto &pe: r) {
    h[pe.first] = q.push(pe.second);
  }

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    for (part_edge_type t: this->at(s.vertex())) {
      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};
        q.modify(h[t.vertex()], t);
      }
    }
  }
  return r;
}

} // namespace graph

#endif // GRAPH_SSSP_LENGTHS
