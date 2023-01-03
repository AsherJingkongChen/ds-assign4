// [GRAPH_Header_Library]
//
#ifndef GRAPH_ASSIGN
#define GRAPH_ASSIGN

namespace graph {

template<
  typename _Ip,
  typename _Wp,
  typename _Tag
>
void simple_graph<_Ip, _Wp, _Tag>::assign(
    _Ip start,
    _Ip end,
    _Wp weight,
    tag::undirected) {

  (*this)[start][end] = weight;
  (*this)[end][start] = weight;
}

template<
  typename _Ip,
  typename _Wp,
  typename _Tag
>
void simple_graph<_Ip, _Wp, _Tag>::assign(
    _Ip start,
    _Ip end,
    _Wp weight,
    tag::directed) {

  (*this)[start][end] = weight;
}

} // namespace graph

#endif // GRAPH_ASSIGN
