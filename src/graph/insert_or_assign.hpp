// [GRAPH_Header_Library]
//
#ifndef GRAPH_INSERT_OR_ASSIGN
#define GRAPH_INSERT_OR_ASSIGN

#include <utility>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
std::pair<
  typename simple_graph<_Ip, _Lp, _DirTag>
  ::const_iterator, 
  bool
>
simple_graph<_Ip, _Lp, _DirTag>::_insert_or_assign(
    index_type const &source,
    index_type const &target,
    length_type const &length,
    tag::undirected) {

  _insert_or_assign(
    target,
    source,
    length,
    tag::directed()
  );

  return
    _insert_or_assign(
      source, 
      target, 
      length, 
      tag::directed()
    );
}

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
std::pair<
  typename simple_graph<_Ip, _Lp, _DirTag>
  ::const_iterator, 
  bool
>
simple_graph<_Ip, _Lp, _DirTag>::_insert_or_assign(
    index_type const &source,
    index_type const &target,
    length_type const &length,
    tag::directed) {

  part_edge_type pe(target, length);

  auto i1 = this->insert({source, {pe}});
  if (i1.second) {
    return {
      {
        i1.first, 
        base_type::end(), 
        i1.first->second.begin()
      },
      true
    };
  }

  auto i2 = i1.first->second.insert(pe);
  if (not i2.second) {
    i2.first->second = length;
  }

  return {
    {
      i1.first, 
      base_type::end(),
      i2.first
    },
    i2.second
  };
}

} // namespace graph

#endif // GRAPH_INSERT_OR_ASSIGN