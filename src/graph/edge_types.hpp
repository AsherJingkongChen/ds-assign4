// [GRAPH_Header_Library]
//
#ifndef GRAPH_EDGE_TYPES
#define GRAPH_EDGE_TYPES

#include <tuple>
#include <utility>

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

  // addition (for comparison):
  //   edge length
  part_edge_type operator+(part_edge_type const &other) const {
    return {
      vertex(), 
      length() + other.length()
    };
  }

  part_edge_type &operator+=(part_edge_type const &other) {
    length() += other.length();
    return *this;
  }

public:
  using std::pair<_Ip, _Lp>::pair;
};

} // namespace graph

#endif // GRAPH_EDGE_TYPES
