// [GRAPH_Header_Library]
//
#ifndef GRAPH_SSSP_LENGTHS
#define GRAPH_SSSP_LENGTHS

#include <queue>
#include <limits>
#include <iostream>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE
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
#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>
::sssp_lengths(index_type const &source) const {
  using priority_queue =
    std::priority_queue<
      part_edge_type,
      std::vector<part_edge_type>,
      std::greater<part_edge_type>
    >;

  if (base_type::find(source) == base_type::end()) {
    return {};
  }

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

#ifdef __HAS_GNU_PBDS_PRIORITY_QUEUE
template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  typename _AlgoTag,
  typename _PqTag,
  typename
    std::enable_if<
      std::is_same<
        _AlgoTag, 
        tag::with_decrease_key
      >::value
    >::type*,
  typename
    std::enable_if<
      not std::is_same<
        _PqTag,
        __gnu_pbds::binary_heap_tag
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
      _PqTag
    >;

  if (base_type::find(source) == base_type::end()) {
    return {};
  }

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
#endif // __HAS_GNU_PBDS_PRIORITY_QUEUE

} // namespace graph

#endif // GRAPH_SSSP_LENGTHS
