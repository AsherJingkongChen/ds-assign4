#include "../../src/xml/xml.hpp"
#include <fstream>

using namespace xml::tag;

int main() {
  auto s = xml::element<svg>::get();
  std::ofstream fout("debug/xml/svg_and_declaration.svg.log");
  fout << xml::declaration() << s->to_string();
}