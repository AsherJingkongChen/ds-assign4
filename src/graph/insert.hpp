// [GRAPH_Header_Library]
//
#ifndef GRAPH_INSERT
#define GRAPH_INSERT

#include <utility>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  bool _Replacing,
  typename __DirTag,
  enable_if_same<
    __DirTag, tag::undirected>
>
std::pair<
  typename simple_graph<_Ip, _Lp, _DirTag>
  ::const_iterator, 
  bool
>
simple_graph<_Ip, _Lp, _DirTag>::_insert_sfinae(
    index_type const &source,
    index_type const &target,
    length_type const &length) {

  auto result = _insert(target, source, length);
  if (result.second) {
    __sources[target] = (__targets[source] = true);
  }

  result = _insert(source, target, length);
  if (result.second) {
    __sources[source] = (__targets[target] = true);
  }

  if (_Replacing) {
    static_cast<base_type&>(*this)[target][source] = length;
    static_cast<base_type&>(*this)[source][target] = length;
  }
  return result;
}

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
template<
  bool _Replacing,
  typename __DirTag,
  enable_if_not_same<
    __DirTag, tag::undirected>,
  enable_if_same<
    __DirTag, tag::directed>
>
std::pair<
  typename simple_graph<_Ip, _Lp, _DirTag>
  ::const_iterator, 
  bool
>
simple_graph<_Ip, _Lp, _DirTag>::_insert_sfinae(
    index_type const &source,
    index_type const &target,
    length_type const &length) {

  auto result = _insert(source, target, length);
  if (result.second) {
    __sources[source] = (__targets[target] = true);
  }

  if (_Replacing) {
    static_cast<base_type&>(*this)[source][target] = length;
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
simple_graph<_Ip, _Lp, _DirTag>::_insert(
    index_type const &source,
    index_type const &target,
    length_type const &length) {

  if (source == target) {
    return {this->end(), false};
  }

  part_edge_type pe(target, length);

  auto i1 = base_type::insert({source, {pe}});
  if (i1.second) {
    return
      {
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

  return
    {
      {
        i1.first, 
        base_type::end(),
        i2.first
      },
      false
    };
}

} // namespace graph

#endif // GRAPH_INSERT
