#include "../../src/graph/graph.hpp"

using namespace __gnu_pbds;

using sg_uuu =
  graph::simple_graph<unsigned, unsigned, graph::tag::undirected>;

using deck = graph::tag::with_decrease_key;
using nodeck = graph::tag::without_decrease_key;

int main() {
  sg_uuu{}.sssp_lengths({});
  sg_uuu{}.sssp_lengths<nodeck>({});
  sg_uuu{}.sssp_lengths<deck>({});
  sg_uuu{}.sssp_lengths<deck, rc_binomial_heap_tag>({});
  sg_uuu{}.sssp_lengths<deck, thin_heap_tag>({});
  sg_uuu{}.sssp_lengths<deck, pairing_heap_tag>({});
  sg_uuu{}.sssp_lengths<deck, binomial_heap_tag>({});

  // sg_uuu{}.sssp_lengths<deck, binary_heap_tag>(0);
  // sg_uuu{}.sssp_lengths<nodeck, pairing_heap_tag>({});
  // sg_uuu{}.sssp_lengths<pairing_heap_tag>({});
}