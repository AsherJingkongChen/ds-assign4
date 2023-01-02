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
#ifndef GRAPH_GRAPH
#define GRAPH_GRAPH

#include <vector>
#include <bitset>

namespace graph {

template<typename _Tp>
class ud_graph {
public:
  typedef uint16_t      size_type;
  typedef size_type     index_type;
  typedef uint32_t      weight_type;
  typedef _Tp           value_tupe;
  typedef _Tp const &   const_reference;
  typedef _Tp &         reference;
  struct edge;

private:
  std::vector<std::vector<edge>> adj_list;

public:
  ud_graph() = default;
  ud_graph(ud_graph const &) = default;
  ud_graph(ud_graph &&) = default;
  ud_graph &operator=(ud_graph const &) = default;
  ud_graph &operator=(ud_graph &&) = default;
};

template<typename _Tp>
struct ud_graph<_Tp>::edge {
  index_type v1;
  index_type v2;
  weight_type w;

  constexpr edge(
    index_type v1, 
    index_type v2,
    weight_type w = 1):

    v1(v1), v2(v2), w(w) {
  }
};

} // namespace graph

#endif // GRAPH_GRAPH
