// [GRAPH_Header_Library]
//
#ifndef GRAPH_ENABLE_IF
#define GRAPH_ENABLE_IF

#include <type_traits>

namespace graph {

template<typename _Tp, typename _Up>
using enable_if_same = 
  typename std::enable_if<
    std::is_same<_Tp, _Up>::value,
    int
  >::type;

template<typename _Tp, typename _Up>
using enable_if_not_same = 
  typename std::enable_if<
    not std::is_same<_Tp, _Up>::value,
    int
  >::type;

template<typename _Tp, typename _Up>
using enable_if_convertible = 
  typename std::enable_if<
    std::is_convertible<_Tp, _Up>::value,
    int
  >::type;

template<typename _Tp, typename _Up>
using enable_if_not_convertible = 
  typename std::enable_if<
    not std::is_convertible<_Tp, _Up>::value,
    int
  >::type;

} // namespace graph

#endif // GRAPH_ENABLE_IF
