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
      if (v[t.vertex()]) { continue; }

      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};

        // only potential source vertices are needed to be pushed in
        //
        // not that if the graph is undirected,
        // a target is always a source;
        // otherwise, it is not always to be
        //
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
//     V := V | {s.v}
//
//     for all E in G that S(E) = s.v {
//       l := s.l + L(E)
//       if T(E) is not in V and R[T(E)].l > s.l + L(E) {
//         R[T(E)] := (v: s.v, l: l)
//         if there is such d that T(E) = S(d) for all d in G {
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
