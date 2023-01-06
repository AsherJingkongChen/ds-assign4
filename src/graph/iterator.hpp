// [GRAPH_Header_Library]
//
#ifndef GRAPH_ITERATOR
#define GRAPH_ITERATOR

#include <iterator>

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
class simple_graph<_Ip, _Lp, _DirTag>::const_iterator {
public:
  typedef std::forward_iterator_tag   iterator_category;
  typedef std::ptrdiff_t              difference_type;
  typedef edge_type                   value_type;
  typedef edge_type const &           reference;
  typedef edge_type const *           pointer;

  typedef 
    typename base_type::const_iterator
    source_iterator;

  typedef
    typename base_type::mapped_type::const_iterator
    target_iterator;

private:
  source_iterator s_it;
  source_iterator s_ed;
  target_iterator t_it;
  value_type      edge;

private:
  bool s_it_valid() const {
    return s_it != s_ed;
  }

  // need s_it to be valid
  //
  bool t_it_valid() const {
    return t_it != s_it->second.end();
  }

public:
  reference operator*() const {
    if (not s_it_valid()) { throw; }
    return edge;
  }

  pointer operator->() const {
    if (not s_it_valid()) { throw; }
    return &edge;
  }

  const_iterator &operator++() {
    if (not s_it_valid()) { throw; }

    ++t_it;

    if (not t_it_valid()) {
      ++s_it;

      if (not s_it_valid()) { 
        t_it = {};
        return *this; 
      }
      t_it = s_it->second.begin();
    }

    update();
    return *this;
  }

  const_iterator operator++(int) {
    auto result(*this);
    ++*this;
    return result;
  }

  bool operator==(const_iterator const &other) const {
    return
      (s_it == other.s_it &&
       s_ed == other.s_ed &&
       t_it == other.t_it);     
  }

  bool operator!=(const_iterator const &other) const {
    return not (*this == other);
  }

private:
  void update() {
    edge = {s_it->first, t_it->first, t_it->second};
  }

public:
  const_iterator(
      source_iterator s_it, 
      source_iterator s_ed,
      target_iterator t_it):

      s_it(s_it),
      s_ed(s_ed),
      t_it(t_it),
      edge() {

    if (s_it_valid() && t_it_valid()) {
      update();
    }
  }

  const_iterator(const_iterator const &source):
    s_it(source.s_it),
    s_ed(source.s_ed),
    t_it(source.t_it),
    edge(source.edge) {
  }

  const_iterator &operator=(const_iterator const &other) {
    s_it = other.s_it;
    s_ed = other.s_ed;
    t_it = other.t_it;
    edge = other.edge;
    return *this;
  }

  const_iterator(const_iterator &&source) noexcept:
    s_it(std::move(source.s_it)),
    s_ed(std::move(source.s_ed)),
    t_it(std::move(source.t_it)),
    edge(std::move(source.edge)) {
  }

  const_iterator &operator=(const_iterator &&other) noexcept {
    s_it = std::move(other.s_it);
    s_ed = std::move(other.s_ed);
    t_it = std::move(other.t_it);
    edge = std::move(other.edge);
    return *this;
  }
};

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
typename simple_graph<_Ip, _Lp, _DirTag>::const_iterator
simple_graph<_Ip, _Lp, _DirTag>::begin() const noexcept {
  auto
  b(base_type::begin()),
  e(base_type::end());

  if (b == e) {
    return {b, e, {}};
  }
  return {b, e, b->second.begin()};
}

template<
  typename _Ip,
  typename _Lp,
  typename _DirTag
>
typename simple_graph<_Ip, _Lp, _DirTag>::const_iterator
simple_graph<_Ip, _Lp, _DirTag>::end() const noexcept {
  return {
    base_type::end(),
    base_type::end(),
    {}
  };
}

} // namespace graph

#endif // GRAPH_ITERATOR
