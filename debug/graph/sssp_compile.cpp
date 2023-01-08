#include "../../src/graph/graph.hpp"

using sg_uuu =
  graph::simple_graph<unsigned, unsigned, graph::tag::undirected>;

int main() {
  sg_uuu{}.sssp({});
  sg_uuu{}.sssp<2>({});

  sg_uuu{}.sssp<graph::tag::std_priority_queue>({});
  sg_uuu{}.sssp<graph::tag::binary_heap>({});
  sg_uuu{}.sssp<graph::tag::binomial_heap>({});
  sg_uuu{}.sssp<graph::tag::pairing_heap>({});
  sg_uuu{}.sssp<graph::tag::rc_binomial_heap>({});
  sg_uuu{}.sssp<graph::tag::thin_heap>({});
  sg_uuu{}.sssp<__gnu_pbds::binary_heap_tag>({});
  sg_uuu{}.sssp<__gnu_pbds::binomial_heap_tag>({});
  sg_uuu{}.sssp<__gnu_pbds::pairing_heap_tag>({});
  sg_uuu{}.sssp<__gnu_pbds::rc_binomial_heap_tag>({});
  sg_uuu{}.sssp<__gnu_pbds::thin_heap_tag>({});

  sg_uuu{}.sssp<graph::tag::std_priority_queue, 2>({});
  sg_uuu{}.sssp<graph::tag::binary_heap, 2>({});
  sg_uuu{}.sssp<graph::tag::binomial_heap, 2>({});
  sg_uuu{}.sssp<graph::tag::pairing_heap, 2>({});
  sg_uuu{}.sssp<graph::tag::rc_binomial_heap, 2>({});
  sg_uuu{}.sssp<graph::tag::thin_heap, 2>({});
  sg_uuu{}.sssp<__gnu_pbds::binary_heap_tag, 2>({});
  sg_uuu{}.sssp<__gnu_pbds::binomial_heap_tag, 2>({});
  sg_uuu{}.sssp<__gnu_pbds::pairing_heap_tag, 2>({});
  sg_uuu{}.sssp<__gnu_pbds::rc_binomial_heap_tag, 2>({});
  sg_uuu{}.sssp<__gnu_pbds::thin_heap_tag, 2>({});

  // sg_uuu{}.sssp<void>({});
}