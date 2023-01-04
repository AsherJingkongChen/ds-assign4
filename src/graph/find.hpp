// [GRAPH_Header_Library]
//
#ifndef GRAPH_FIND
#define GRAPH_FIND

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _Tag
>
typename simple_graph<_Ip, _Lp, _Tag>::const_iterator
simple_graph<_Ip, _Lp, _Tag>::find(
    index_type const &source,
    index_type const &target) const {

  auto i1 = base_type::find(source);
  if (i1 == base_type::end()) {
    return this->end();
  }

  auto i2 = i1->second.find(target);
  if (i2 == i1->second.end()) {
    return this->end();
  }

  return {i1, base_type::end(), i2};
}

} // namespace graph

#endif // GRAPH_FIND
