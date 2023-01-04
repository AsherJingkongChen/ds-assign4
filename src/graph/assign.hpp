// [GRAPH_Header_Library]
//
#ifndef GRAPH_ASSIGN
#define GRAPH_ASSIGN

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _Tag
>
void simple_graph<_Ip, _Lp, _Tag>::assign(
    _Ip start,
    _Ip end,
    _Lp length,
    tag::undirected) {

  (*this)[start][end] = length;
  (*this)[end][start] = length;
}

template<
  typename _Ip,
  typename _Lp,
  typename _Tag
>
void simple_graph<_Ip, _Lp, _Tag>::assign(
    _Ip start,
    _Ip end,
    _Lp length,
    tag::directed) {

  (*this)[start][end] = length;
}

} // namespace graph

#endif // GRAPH_ASSIGN
