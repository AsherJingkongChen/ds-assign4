// [GRAPH_Header_Library]
//
#ifndef GRAPH_EDGES
#define GRAPH_EDGES

namespace graph {

template<
  typename _Ip,
  typename _Wp,
  typename _Tag
>
typename simple_graph<_Ip, _Wp, _Tag>::edge_list 
simple_graph<_Ip, _Wp, _Tag>::edges() const {
  edge_list result;
  for (auto &p: *this) {
    for (auto &q: p.second) {
      result.emplace_back(p.first, q.first, q.second);
    }
  }
  return result;
}

} // namespace graph

#endif // GRAPH_EDGES
