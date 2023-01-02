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

#include <cstdint>
#include <unordered_map>

// graph:
// <vertex index type, edge weight type>
//
template<
  typename _Ip = uint32_t, 
  typename _Wp = uint32_t
>
struct graph {

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
typedef vertex_list<vertex_list<weight_type>> adj_list;

};

#endif // GRAPH_GRAPH
