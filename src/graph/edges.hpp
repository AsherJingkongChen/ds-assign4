// [GRAPH_Header_Library]
//
#ifndef GRAPH_EDGES
#define GRAPH_EDGES

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _Tag
>
typename simple_graph<_Ip, _Lp, _Tag>::edge_list 
simple_graph<_Ip, _Lp, _Tag>::edges() const {
  edge_list result;
  for (auto &p1: *this) {
    for (auto &p2: p1.second) {
      result.emplace_back(p1.first, p2.first, p2.second);
    }
  }
  return result;
}

} // namespace graph

#endif // GRAPH_EDGES
