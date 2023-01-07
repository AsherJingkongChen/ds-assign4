// [GRAPH_Header_Library]
//
#ifndef GRAPH_SSSP_LENGTHS
#define GRAPH_SSSP_LENGTHS

#include <queue>
#include <limits>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp_lengths_std(
    index_type const &source,
    tag::undirected) const {

  using priority_queue =
    std::priority_queue<
      part_edge_type,
      std::vector<part_edge_type>,
      std::greater<part_edge_type>
    >;

  if (sources.find(source) == sources.end()) {
    return {};
  }

  part_edge_list r;
  for (auto &p: targets) {
    r[p.first] = {
      p.first,
      std::numeric_limits<length_type>::max()
    };
  }

  priority_queue q;
  q.push({
    source,
    (r[source].length() = length_type())
  });

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    for (part_edge_type t: base_type::at(s.vertex())) {
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
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp_lengths_std(
    index_type const &source,
    tag::directed) const {

  using priority_queue =
    std::priority_queue<
      part_edge_type,
      std::vector<part_edge_type>,
      std::greater<part_edge_type>
    >;

  if (sources.find(source) == sources.end()) {
    return {};
  }

  part_edge_list r;
  for (auto &p: targets) {
    r[p.first] = {
      p.first,
      std::numeric_limits<length_type>::max()
    };
  }

  priority_queue q;
  q.push({
    source,
    (r[source].length() = length_type())
  });

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    for (part_edge_type t: base_type::at(s.vertex())) {
      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};

        // for directed graph: 
        //   targets are not necessarily sources
        //
        if (sources.find(t.vertex()) != sources.end()) {
          q.push(t);
        }
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
template<typename _PqTag>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp_lengths_gnu_pbds(
    index_type const &source, 
    tag::undirected) const {

  static_assert(
    not std::is_same<_PqTag, __gnu_pbds::binary_heap_tag>::value,
    "__gnu_pbds::binary_heap_tag is not available for _PqTag in "
    "graph::simple_graph<_Ip, _Lp, _DirTag>"
    "::sssp_length<_AlgoTag, _PqTag>(const index_type&) "
    "due to some performance issues"
  );

  using priority_queue = 
    __gnu_pbds::priority_queue<
      part_edge_type,
      std::greater<part_edge_type>,
      _PqTag
    >;

  if (sources.find(source) == sources.end()) {
    return {};
  }

  part_edge_list r;
  for (auto &p: targets) {
    r[p.first] = {
      p.first,
      std::numeric_limits<length_type>::max()
    };
  }

  r[source].length() = length_type();

  priority_queue q;
  node_list<typename priority_queue::point_iterator> h;
  for (auto &ppe: r) {
    h[ppe.first] = q.push(ppe.second);
  }

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    for (part_edge_type t: base_type::at(s.vertex())) {
      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};
        q.modify(h[t.vertex()], t);
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
template<typename _PqTag>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp_lengths_gnu_pbds(
    index_type const &source, 
    tag::directed) const {

  static_assert(
    not std::is_same<_PqTag, __gnu_pbds::binary_heap_tag>::value,
    "__gnu_pbds::binary_heap_tag is not available for _PqTag in "
    "graph::simple_graph<_Ip, _Lp, _DirTag>"
    "::sssp_length<_AlgoTag, _PqTag>(const index_type&) "
    "due to some performance issues"
  );

  using priority_queue = 
    __gnu_pbds::priority_queue<
      part_edge_type,
      std::greater<part_edge_type>,
      _PqTag
    >;

  if (sources.find(source) == sources.end()) {
    return {};
  }

  part_edge_list r;
  for (auto &p: targets) {
    r[p.first] = {
      p.first,
      std::numeric_limits<length_type>::max()
    };
  }

  r[source].length() = length_type();

  priority_queue q;
  node_list<typename priority_queue::point_iterator> h;
  for (auto &ppe: r) {
    // for directed graph: 
    //   targets are not necessarily sources
    //
    if (sources.find(ppe.first) != sources.end()) {
      h[ppe.first] = q.push(ppe.second);
    }
  }

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    for (part_edge_type t: base_type::at(s.vertex())) {
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
