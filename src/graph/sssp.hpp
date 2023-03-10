// [GRAPH_Header_Library]
//
#ifndef GRAPH_SSSP
#define GRAPH_SSSP

#include <queue>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  typename _PqTag,
  _Lp _LengthMax,
  enable_if_same<
    _PqTag, tag::std_priority_queue>
>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp_sfinae(
    index_type const &source) const {

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
template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  typename _PqTag,
  _Lp _LengthMax,
  enable_if_not_same<
    _PqTag, tag::std_priority_queue>,
  enable_if_convertible<
    _PqTag, __gnu_pbds::priority_queue_tag>
>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp_sfinae(
    index_type const &source) const {

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

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  typename _PriorityQueue,
  _Lp _LengthMax
>
typename simple_graph<_Ip, _Lp, _DirTag>::part_edge_list
simple_graph<_Ip, _Lp, _DirTag>::_sssp(
    index_type const &source) const {

  if (__sources.find(source) == __sources.end()) {
    return {};
  }

  part_edge_list r;
  for (auto &p: __targets) {
    r[p.first] = {p.first, _LengthMax};
  }

  _PriorityQueue q;
  q.push({
    source,
    (r[source].length() = length_type())
  });

  node_list<bool> v;

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    v[s.vertex()] = true;

    for (part_edge_type t: base_type::at(s.vertex())) {
      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};

        // only unvisited potential source vertices
        // are needed to be pushed into min-priority queue
        //
        // not that if the graph is undirected,
        // a target is always a source;
        // otherwise, it is not always to be
        //
        if (v[t.vertex()]) { continue; }
        if (std::is_same<_DirTag, tag::undirected>::value || 
            __sources.find(t.vertex()) != __sources.end()) {

          q.push(t);
        }
      }
    }
  }

  // erase unreachable targets
  //
  for (auto i = r.begin(), e = r.end(); i != e;) {
    if (i->first == i->second.vertex()) {
      i = r.erase(i);
    } else {
      ++i;
    }
  }
  return r;
}

} // namespace graph

#endif // GRAPH_SSSP

// pseudocode for this version of Dijkstra's algorithm:
//
// S(E) {
//   return the source vertex in edge E
// }
//
// T(E) {
//   return the target vertex in edge E
// }
//
// L(E) {
//   return the length of edge E
// }
//
// sssp(x, G) {
//   # 1. The given source vertex is x
//   # 2. The graph G is {E[i]}
//   #    where Ei is the ith edge in G
//
//   R := {}
//   for all E in G {
//     R[T(E)] := (v: T(E), l: +INF)
//   }
//   R[x] := (v: x, l: 0)
//
//   Q := {R[x]}
//   V := {}
//
//   while Q != {} {
//     s := extract p in Q with the lowest l
//
//     V := V | {s.v}
//
//     for all E in G that S(E) = s.v {
//       l := s.l + L(E)
//       if R[T(E)].l > l {
//         R[T(E)] := (v: s.v, l: l)
//
//         if T(E) is in V { continue }
//
//         if there is such E' that T(E) = S(E') for all E' in G {
//           Q := Q | (v: T(E), l: L(E))
//         }
//       }
//     }
//   }
//
//   return R without any t = r[t].v
//
//   # R is {r[t]} where r[t] is a pair (v, l)
//   # that represents from vertex x to t has the shortest path lengths l
//   # and the path has a vertex v prior to t
// }
//
