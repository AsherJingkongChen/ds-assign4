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
typename simple_graph<_Ip, _Lp, _Tag>::part_edge_list
simple_graph<_Ip, _Lp, _Tag>
::sssp_lengths(index_type const &source) const {
  part_edge_list r;

  for (auto &e: *this) {
    r[e.source()].length() = 
      std::numeric_limits<length_type>::max();
  }

  std::priority_queue<
    part_edge_type,
    std::vector<part_edge_type>,
    std::greater<part_edge_type>
  >
  q({}, {{source, length_type()}});

  while (not q.empty()) {
    part_edge_type s(q.top()); q.pop();

    if (not (s.length() > r[s.vertex()].length())) {
      r[s.vertex()].length() = s.length();

      for (part_edge_type t: this->at(s.vertex())) {
        if (r[t.vertex()].length() > t.length() + s.length()) {
          r[t.vertex()].length() = (t.length() += s.length());
          r[t.vertex()].vertex() = s.vertex();
          q.push(t);
        }
      }
    }
  }
  return r;
}

} // namespace graph

#endif // GRAPH_SSSP_LENGTHS
