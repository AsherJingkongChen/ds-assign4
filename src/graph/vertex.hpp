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
#ifndef GRAPH_VERTEX
#define GRAPH_VERTEX

#include <utility>

namespace graph {

template<typename _Tp>
class vertex {
public:
  typedef _Tp           value_type;
  typedef _Tp const &   const_reference;
  typedef _Tp &         reference;

public:
  value_type  data;
  bool        visited;

public:
  vertex():
    data(),
    visited(false) {
  }

  vertex(const_reference data):
    data(data),
    visited(false) {
  }

  vertex(value_type &&data):
    data(std::move(data)),
    visited(false) {
  }

  vertex(vertex const &source):
    data(source.data),
    visited(source.visited) {
  }

  vertex(vertex &&source) noexcept:
    data(std::move(source.data)),
    visited(std::move(source.visited)) {
  }

  vertex &operator=(vertex const &other) {
    data = other.data;
    visited = other.visited;
    return *this;
  }

  vertex &operator=(vertex &&other) noexcept {
    data = std::move(other.data);
    visited = std::move(other.visited);
    return *this;
  }

};

} // namespace graph

#endif // GRAPH_VERTEX
