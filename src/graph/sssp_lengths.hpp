// [GRAPH_Header_Library]
//
#ifndef GRAPH_SSSP_LENGTHS
#define GRAPH_SSSP_LENGTHS

#include <queue>
#include <numeric>

#ifdef __GNUG__
#include <ext/pb_ds/priority_queue.hpp>
#endif // __GNUG__

namespace graph {

template<
  typename _Ip,
  typename _Lp,
  typename _Tag
>
typename simple_graph<_Ip, _Lp, _Tag>::length_list
simple_graph<_Ip, _Lp, _Tag>::sssp_lengths(_Ip source) const {
  typename simple_graph<_Ip, _Lp, _Tag>::length_list d;

  for (auto &p1: *this) {
    d[p1.first] = std::numeric_limits<_Lp>::max();
  }

  using _LIp = std::pair<_Lp, _Ip>;
  std::priority_queue<
    _LIp,
    std::vector<_LIp>,
    std::greater<_LIp>
  >
  q({}, {_LIp(_Lp(), source)});

  while (not q.empty()) {
    _Lp l(q.top().first);
    _Ip s(q.top().second);
    q.pop();

    if (not (d[s] < l)) {
      d[s] = l;
      for (auto &p2: this->at(s)) {
        _Ip e(p2.first);
        _Lp w(p2.second);
        if (d[e] > l + w) {
          q.emplace((d[e] = l + w), e);
        }
      }
    }
  }
  return d;
}

} // namespace graph

#endif // GRAPH_SSSP_LENGTHS
