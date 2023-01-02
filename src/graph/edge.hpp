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
#ifndef GRAPH_EDGE
#define GRAPH_EDGE

#include <cstdint>
#include <functional>
#include <iostream>

namespace graph {

typedef uint32_t  index_type;
typedef uint32_t  weight_type;

class edge {
public:
  index_type s;
  index_type e;
  weight_type w;

public:
  bool operator==(edge const &other) const {
    return
      s == other.s &&
      e == other.e &&
      w == other.w;
  }

  bool operator!=(edge const &other) const {
    return !(*this == other);
  }

  bool operator<(edge const &other) const {
    return w < other.w;
  }

  bool operator>(edge const &other) const {
    return w > other.w;
  }

  friend std::istream &operator>>(
      std::istream &in,
      edge &other) {

    return 
      in >> 
      other.s >> 
      other.e >> 
      other.w;
  }

  friend std::ostream &operator<<(
      std::ostream &out,
      edge const &other) {

    return (out << other.s << ' ' 
                << other.e << ' ' 
                << other.w << '\n');
  }

public:
  constexpr edge(
    index_type s, 
    index_type e):

    s(s), e(e), w(1) {
  }

  constexpr edge(
    index_type s, 
    index_type e,
    weight_type w):

    s(s), e(e), w(w) {
  }

  constexpr edge(edge const &source):
    s(source.s),
    e(source.e),
    w(source.w) {
  }

  edge &operator=(edge const &other) {
    s = other.s;
    e = other.e;
    w = other.w;
    return *this;
  }
};

} // namespace graph

namespace std {
  template<>
  struct hash<graph::edge> {
    std::size_t operator()(
        graph::edge const &other) const noexcept {

      return
        (static_cast<uint64_t>(other.s) << 32) |
         static_cast<uint64_t>(other.e);
    }
  };
}

#endif // GRAPH_EDGE
