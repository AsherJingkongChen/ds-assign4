#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>

// example
//
// binary_heap_tag
// binomial_heap_tag
// pairing_heap_tag
// rc_binomial_heap_tag
// thin_heap_tag
//
int main() {
  __gnu_pbds::priority_queue<
    int, 
    std::less<int>, 
    __gnu_pbds::binary_heap_tag
  >
  pq;

  pq.push(5);
  pq.push(4);
  pq.push(1);
  pq.push(2);
  pq.push(3);

  for (; not pq.empty(); pq.pop()) {
    std::cout << pq.top() << " ";
  }
  std::cout << std::endl;
}