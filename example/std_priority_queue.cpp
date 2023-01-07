#include <queue>
#include <iostream>

// example
// > __EXNAME=example/std_priority_queue; g++ $__EXNAME.cpp -o $__EXNAME && ./$__EXNAME && rm -r $__EXNAME
//
int main() {
  std::priority_queue<
    int, 
    std::vector<int>, 
    std::less<int>
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