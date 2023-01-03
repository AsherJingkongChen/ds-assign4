// [GRAPH_Header_Library]
//
#ifndef GRAPH_SHORTEST_PATH
#define GRAPH_SHORTEST_PATH

namespace graph {

template<
  typename _Ip,
  typename _Wp,
  typename _Tag
>
typename simple_graph<_Ip, _Wp, _Tag>::node_list<_Wp>
simple_graph<_Ip, _Wp, _Tag>
::shortest_paths(_Ip source) const {

  return {};
}

} // namespace graph

#endif // GRAPH_SHORTEST_PATH
