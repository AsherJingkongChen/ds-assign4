#include "../../src/geo/geo.hpp"
#include "../../src/xml/xml.hpp"

using namespace xml::tag;

int main() {
  auto root = xml::element<svg>::get();
  auto center = geo::vec2(50, 50);
  xml::element<svg>::get(root)->width = geo::x_str(center * 2.0F);
  xml::element<svg>::get(root)->height = geo::y_str(center * 2.0F);
  for (int i = 0; i < 10; i++) {
    auto a_circle = xml::element<circle>::get();
    xml::element<circle>::get(a_circle)->cx = 
      geo::x_str(
        center + 
        geo::polar(
          geo::x(center) - 6.0F,
          i / 10.0F
        )
      );

    xml::element<circle>::get(a_circle)->cy = 
      geo::y_str(
        center + 
        geo::polar(
          geo::y(center) - 6.0F,
          i / 10.0F
        )
      );

    xml::element<circle>::get(a_circle)->r = "5";

    root->children.push_back(a_circle);
  }

  std::cout << xml::declaration() << root->to_string();
}
