#include "../../src/svg/svg.hpp"
#include <iostream>

int main() {
  auto s = svg::element_ptr(new svg::element_svg);
  std::cout << svg::xml_declaration() << s->to_string();
}