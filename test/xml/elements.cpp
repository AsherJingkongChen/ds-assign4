#include "../../src/xml/xml.hpp"
#include <iostream>

using namespace xml;

int main() {
  auto s = element<tag::svg>::get();
  element<tag::svg>::get(s)->width = "20";
  element<tag::svg>::get(s)->height = "20";
  s = element<tag::svg>::get();
  element<tag::svg>::get(s)->width = "25";
  element<tag::svg>::get(s)->height = "25";
  std::cout << xml_declaration() << s->to_string();
}