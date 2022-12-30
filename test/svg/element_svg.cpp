#include "../../src/svg/svg.hpp"
#include <iostream>

int main() {
  auto s = svg::element;
  dynamic_cast<svg::element_svg*>(s.get())->width = "20";
  dynamic_cast<svg::element_svg*>(s.get())->height = "20";
  std::cout << svg::xml_declaration() << s->to_string();
}