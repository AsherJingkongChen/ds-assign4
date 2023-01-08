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

  if (sources.find(source) == sources.end()) {
    return {};
  }

  node_list<bool> v;
  part_edge_list r;
  for (auto &p: targets) {
    r[p.first] = {p.first, _LengthMax};
  }

  _PriorityQueue q;
  q.push({
    source,
    (r[source].length() = length_type())
  });

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();
  
    if (v[s.vertex()]) { continue; }
    v[s.vertex()] = true;

    for (part_edge_type t: base_type::at(s.vertex())) {
      t += s;
      if (r[t.vertex()] > t) {
        r[t.vertex()] = {s.vertex(), t.length()};

        // only potential source vertices are needed to be pushed in
        //
        // not that if the graph is undirected,
        // a target is always a source;
        // otherwise, it is not always to be
        //
        if ((std::is_same<_DirTag, tag::undirected>::value || 
             sources.find(t.vertex()) != sources.end())) {

          q.push(t);
        }
      }
    }
  }
  return r;
}

} // namespace graph

#endif // GRAPH_SSSP
