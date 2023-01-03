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
  typename simple_graph<_Ip, _Wp, _Tag>
  ::node_list<_Wp> dist;
  typename simple_graph<_Ip, _Wp, _Tag>
  ::node_list<bool> vis;

  dist.reserve(this->size());
  vis.reserve(this->size());

  for (auto &p1: *this) {
    dist.emplace(p1.first, std::numer);

  }

  // dist[source] = 0;
  // std::priority_queue<
  //   std::pair<int, int>, 
  //   std::vector<std::pair<int, int>>, 
  //   std::greater<std::pair<int, int>>
  // > PQ{{}, {{0, source}}};
  // while (not PQ.empty()) {
  //   int u = PQ.top().second;
  //   PQ.pop();
  //   if (vis[u]) continue; // not first extraction
  //   vis[u] = true;
  //   for (auto &edge : G[u]) {
  //     int v = edge.first, l = edge.second;
  //     if (dist[u]+l < dist[v]) {
  //       dist[v] = dist[u]+l;
  //       PQ.push({dist[v], v});
  //     }
  //   }
  // }
  return (dist.begin(), dist.end());
}

} // namespace graph

#endif // GRAPH_SHORTEST_PATHS
