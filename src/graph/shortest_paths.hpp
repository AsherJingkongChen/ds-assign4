// [GRAPH_Header_Library]
//
#ifndef GRAPH_SHORTEST_PATHS
#define GRAPH_SHORTEST_PATHS

#include <queue>
#include <numeric>

#ifdef __GNUG__
#include <ext/pb_ds/priority_queue.hpp>
#endif // __GNUG__

namespace graph {

// std::priority_queue, without decrease key
//
template<
  typename _Ip,
  typename _Wp,
  typename _Tag
>
typename simple_graph<_Ip, _Wp, _Tag>::node_list<_Wp>
simple_graph<_Ip, _Wp, _Tag>::shortest_paths(_Ip source) const {
  typename simple_graph<_Ip, _Wp, _Tag>::node_list<_Wp> d;

  for (auto &p1: *this) {
    d[p1.first] = std::numeric_limits<_Wp>::max();
  }

  using _WIp = std::pair<_Wp, _Ip>;
  std::priority_queue<
    _WIp,
    std::vector<_WIp>,
    std::greater<_WIp>
  >
  q({}, {_WIp(_Wp(), source)});

  while (not q.empty()) {
    _Wp l(q.top().first);
    _Ip s(q.top().second);
    q.pop();

    if (not (d[s] < l)) {
      d[s] = l;
      for (auto &p2: this->at(s)) {
        _Ip e(p2.first);
        _Wp w(p2.second);
        if (d[e] > l + w) {
          q.emplace((d[e] = l + w), e);
        }
      }
    }
  }
  return d;
}

} // namespace graph

#endif // GRAPH_SHORTEST_PATHS
