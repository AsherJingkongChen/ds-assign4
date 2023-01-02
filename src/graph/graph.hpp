// [GRAPH_Header_Library]
//
// MIT License
//
// Copyright (C) 2023 Asher Chen
// 
// Permission is hereby granted, free of charge, 
// to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), 
// to deal in the Software without restriction, 
// including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and 
// this permission notice shall be included 
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", 
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
// THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Note:
// this is an adapter header for standard C++ library
//
#ifndef GRAPH_GRAPH
#define GRAPH_GRAPH

#include <cstdint>
#include <utility>
#include <iostream>
#include <type_traits>
#include <unordered_map>

// graph:
// <vertex index type, edge weight type>
//
template<
  typename _Ip = uint32_t, 
  typename _Wp = uint32_t
>
struct graph {
  static_assert(
    std::is_unsigned<_Wp>::value, 
    "edge weight is currently "
    "only available as unsigned integer type"
  );

  typedef _Ip index_type;
  typedef _Wp weight_type;

  // vertex list: 
  // <vertex index, custom value>
  //
  template<typename value_type>
  using vertex_list = 
    std::unordered_map<index_type, value_type>;

  // adjacency list: 
  // <start vertex index, <end vertex index, edge weight>>
  //
  class adj_list: 
    public vertex_list<
      vertex_list<weight_type>
    > {

  public:
    adj_list &connect(
        index_type start, 
        index_type end,
        weight_type weight) {

      auto s = this->find(start);
      auto e = this->find(end);

      if (s == this->end()) {
        this->insert({start, {{end, weight}}});

      } else {
        s->second[end] = weight;
      }

      if (e == this->end()) {
        this->insert({end, {{start, weight}}});

      } else {
        e->second[start] = weight;
      }

      return *this;
    }

    using
      vertex_list<vertex_list<weight_type>>
      ::vertex_list;

  }; // class adj_list

}; // struct graph

template<typename _Tp, typename _Up>
std::istream &operator>>(
    std::istream &in,
    std::pair<const _Tp, _Up> &other) {

  return (in >> other.first >> other.second);
}

template<typename _Tp, typename _Up>
std::ostream &operator<<(
    std::ostream &out,
    std::pair<const _Tp, _Up> const &other) {

  return (out << other.first << ' ' << other.second);
}

#endif // GRAPH_GRAPH
