#include "../../src/math/math.hpp"
#include <fstream>

int main() {
  int I = 10;
  std::ofstream fout("debug/math/vec2.out.log");

  for (int i = I; i--;) {
    fout << math::polar(5.0F, i / float(I)) + 
            math::vec2(5, 5) << "\n";
  }
}