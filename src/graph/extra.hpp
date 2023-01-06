// [GRAPH_Header_Library]
//
#ifndef GRAPH_EXTRA
#define GRAPH_EXTRA

#include <iostream>

namespace graph {

namespace extra {

namespace io {

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

} // namespace io

} // namespace extra

} // namespace graph

#endif // GRAPH_EXTRA