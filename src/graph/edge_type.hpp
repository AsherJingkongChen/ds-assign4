// [GRAPH_Header_Library]
//
#ifndef GRAPH_EDGE_TYPE
#define GRAPH_EDGE_TYPE

#include <tuple>
#include <utility>
#include <iostream>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
class simple_graph<_Ip, _Lp, _DirTag>::edge_type:
  public std::tuple<_Ip, _Ip, _Lp> {

public:
  typedef _Ip index_type;
  typedef _Lp length_type;

public:
  index_type const &source() const noexcept {
    return std::get<0>(*this);
  }

  index_type const &target() const noexcept {
    return std::get<1>(*this);
  }

  length_type const &length() const noexcept {
    return std::get<2>(*this);
  }

  index_type &source() noexcept {
    return std::get<0>(*this);
  }

  index_type &target() noexcept {
    return std::get<1>(*this);
  }

  length_type &length() noexcept {
    return std::get<2>(*this);
  }

public:
  // equality:
  //   source index and target index
  //
  bool operator==(edge_type const &other) const {
    return equal_to(other, _DirTag());
  }

  bool operator!=(edge_type const &other) const {
    return not equal_to(other, _DirTag());
  }

  // comparison:
  //   edge length
  //
  bool operator<(edge_type const &other) const {
    return length() < other.length();
  }

  bool operator>(edge_type const &other) const {
    return length() > other.length();
  }

private:
  bool equal_to(
      edge_type const &other, 
      tag::undirected) const {

    return 
      (source() == other.source() &&
       target() == other.target())
      ||
      (source() == other.target() &&
       target() == other.source());
  }

  bool equal_to(
      edge_type const &other,
      tag::directed) const {

    return 
      source() == other.source() &&
      target() == other.target();
  }

public:
  using std::tuple<_Ip, _Ip, _Lp>::tuple;
};

} // namespace graph

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
class simple_graph<_Ip, _Lp, _DirTag>::part_edge_type:
  public std::pair<_Ip, _Lp> {

public:
  typedef _Ip index_type;
  typedef _Lp length_type;

public:
  index_type const &vertex() const noexcept {
    return this->first;
  }

  length_type const &length() const noexcept {
    return this->second;
  }

  index_type &vertex() noexcept {
    return this->first;
  }

  length_type &length() noexcept {
    return this->second;
  }

public:
  // equality:
  //   vertex index and edge length
  //
  bool operator==(part_edge_type const &other) const {
    return
      vertex() == other.vertex() &&
      length() == other.length();
  }

  bool operator!=(part_edge_type const &other) const {
    return not (*this == other);
  }

  // comparison:
  //   edge length
  //
  bool operator<(part_edge_type const &other) const {
    return length() < other.length();
  }

  bool operator>(part_edge_type const &other) const {
    return length() > other.length();
  }

public:
  using std::pair<_Ip, _Lp>::pair;
};

} // namespace graph

template<typename _Tp, typename _Up>
std::ostream &operator<<(
    std::ostream &o, 
    std::pair<_Tp, _Up> const &p) {
  
  return (o << p.first << ' ' << p.second);
}

template<typename _Tp, typename _Up>
std::istream &operator>>(
    std::istream &i, 
    std::pair<_Tp, _Up> &p) {
  
  return (i >> p.first >> p.second);
}

template<
  std::size_t _Sz,
  typename... _Args,
  typename std::enable_if<_Sz == 1>::type* = nullptr
>
std::ostream &operator<<(
    std::ostream &o, 
    std::tuple<_Args...> const &t) {

  return o << std::get<_Sz - 1>(t);
}

template<
  std::size_t _Sz,
  typename... _Args,
  typename std::enable_if<(_Sz > 1)>::type* = nullptr
>
std::ostream &operator<<(
    std::ostream &o, 
    std::tuple<_Args...> const &t) {

  return 
    operator<< <_Sz - 1, _Args...>(o, t) << ' ' 
            << std::get<_Sz - 1>(t);
}

template<typename... _Args>
std::ostream &operator<<(
    std::ostream &o, 
    std::tuple<_Args...> const &t) {

  return operator<< <sizeof...(_Args), _Args...>(o, t);
}

template<
  std::size_t _Sz,
  typename... _Args,
  typename std::enable_if<_Sz == 1>::type* = nullptr
>
std::istream &operator>>(
    std::istream &i, 
    std::tuple<_Args...> &t) {

  return i >> std::get<_Sz - 1>(t);
}

template<
  std::size_t _Sz,
  typename... _Args,
  typename std::enable_if<(_Sz > 1)>::type* = nullptr
>
std::istream &operator>>(
    std::istream &i, 
    std::tuple<_Args...> &t) {

  return
    operator>> <_Sz - 1, _Args...>(i, t)
            >> std::get<_Sz - 1>(t);
}

template<typename... _Args>
std::istream &operator>>(
    std::istream &i, 
    std::tuple<_Args...> &t) {

  return operator>> <sizeof...(_Args), _Args...>(i, t);
}

#endif // GRAPH_EDGE_TYPE
