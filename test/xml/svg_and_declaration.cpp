#include "../../src/xml/xml.hpp"
#include <iostream>

using namespace xml::tag;

int main() {
  auto s = xml::element<svg>::get();
  xml::element<svg>::get(s)->width = "20";
  xml::element<svg>::get(s)->height = "20";
  {
    auto t = xml::element<svg>::get(s);
    xml::element<svg>::get(t)->width = "25";
    xml::element<svg>::get(t)->height = "25";
  }
  std::cout << xml::declaration() << s->to_string();
}