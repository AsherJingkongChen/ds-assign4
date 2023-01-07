#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>

template<typename _Tp>
struct myless {
  bool operator()(_Tp const &a, _Tp const &b) const {
    return a < b;
  }
};

// example
// > __EXNAME=example/gnu_pbds_priority_queue; g++ $__EXNAME.cpp -o $__EXNAME && ./$__EXNAME && rm -r $__EXNAME
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
    myless<int>, 
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