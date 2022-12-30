#include "../../src/svg/svg.hpp"
#include <iostream>

int main() {
  auto s = new svg::element_svg;
  std::cout << svg::xml_declaration() << s->to_string();
  delete s;
}