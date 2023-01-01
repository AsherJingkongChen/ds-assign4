#include "../../src/geo/geo.hpp"
#include <fstream>

int main() {
  int I = 10;
  std::ofstream fout("test/geo/vec2.out.log");
  for (int i = I; i--;) {
    
    fout << geo::polar(5, i / float(I)) + 
            geo::vec2(5, 5) << "\n";
  }
}