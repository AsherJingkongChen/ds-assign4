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
  typedef std::tuple<_Ip, _Ip, _Lp> base_type;
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
  bool operator==(edge_type const &other) const {
    return equal_to(other, _DirTag());
  }

  bool operator!=(edge_type const &other) const {
    return not equal_to(other, _DirTag());
  }

  bool operator<(edge_type const &other) const {
    if (length() == other.length()) {
      if (source() == other.source()) {
        return target() < other.target();
      }
      return source() < other.source();
    }
    return length() < other.length();
  }

  bool operator>(edge_type const &other) const {
    if (length() == other.length()) {
      if (source() == other.source()) {
        return target() > other.target();
      }
      return source() > other.source();
    }
    return length() > other.length();
  }

private:
  bool equal_to(
      edge_type const &other, 
      tag::undirected) const {

    return 
      (source() == other.source() &&
       target() == other.target() &&
       length() == other.length())
      ||
      (source() == other.target() &&
       target() == other.source());
  }

  bool equal_to(
      edge_type const &other,
      tag::directed) const {

    return 
      source() == other.source() &&
      target() == other.target() &&
      length() == other.length();
  }

public:
  using base_type::base_type;
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
  typedef std::pair<_Ip, _Lp> base_type;
  typedef _Ip index_type;
  typedef _Lp length_type;

public:
  index_type const &vertex() const noexcept {
    return base_type::first;
  }

  length_type const &length() const noexcept {
    return base_type::second;
  }

  index_type &vertex() noexcept {
    return base_type::first;
  }

  length_type &length() noexcept {
    return base_type::second;
  }

public:
  bool operator==(part_edge_type const &other) const {
    return
      vertex() == other.vertex() &&
      length() == other.length();
  }

  bool operator!=(part_edge_type const &other) const {
    return not (*this == other);
  }

  bool operator<(part_edge_type const &other) const {
    if (length() == other.length()) {
      return vertex() < other.vertex();
    }
    return length() < other.length();
  }

  bool operator>(part_edge_type const &other) const {
    if (length() == other.length()) {
      return vertex() > other.vertex();
    }
    return length() > other.length();
  }

  // addition:
  //   edge length
  //
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
  using base_type::base_type;
};

} // namespace graph

#endif // GRAPH_EDGE_TYPES
