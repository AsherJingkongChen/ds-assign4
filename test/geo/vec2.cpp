#include "../../src/geo/geo.hpp"
#include <iostream>

int main() {
  int I = 10;
  for (int i = I; i--;) {
    std::cout << geo::polar(5, i / float(I)) + 
                 geo::vec2(5, 5) << "\n";
  }
}