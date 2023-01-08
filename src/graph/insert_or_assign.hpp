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

  auto result = _insert_or_assign(target, source, length);
  if (result.second) {
    sources[target] = (targets[source] = true);
  }

  result = _insert_or_assign(source, target, length);
  if (result.second) {
    sources[source] = (targets[target] = true);
  }

  return result;
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
  
  auto result = _insert_or_assign(source, target, length);

  if (result.second) {
    sources[source] = (targets[target] = true);
  }

  return result;
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
    length_type const &length) {

  part_edge_type pe(target, length);

  auto i1 = base_type::insert({source, {pe}});
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
  if (i2.second) {
    return
      {
        {
          i1.first, 
          base_type::end(),
          i2.first
        },
        true
      };
  }

  i2.first->second = length;
  return {
    {
      i1.first, 
      base_type::end(),
      i2.first
    },
    false
  };
}

} // namespace graph

#endif // GRAPH_INSERT_OR_ASSIGN
