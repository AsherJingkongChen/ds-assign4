#include "../../src/geo/geo.hpp"
#include "../../src/xml/xml.hpp"
#include <fstream>

using namespace xml::tag;

int main() {
  auto root = xml::element<svg>::get();
  auto center = geo::vec2(50, 50);
  auto count = 10;
  auto radius = 5.0F;
  xml::element<svg>::get(root)->width = geo::x_str(center * 2.0F);
  xml::element<svg>::get(root)->height = geo::y_str(center * 2.0F);
  root->fill = "black";
  root->stroke = "";
  root->stroke_width = "0";

  for (int i = 0; i < count; i++) {
    auto a_circle = xml::element<circle>::get();
    xml::element<circle>::get(a_circle)->cx = 
      geo::x_str(
        center + 
        geo::polar(
          geo::x(center) - radius,
          i / float(count)
        )
      );

    xml::element<circle>::get(a_circle)->cy = 
      geo::y_str(
        center + 
        geo::polar(
          geo::y(center) - radius,
          i / float(count)
        )
      );

    xml::element<circle>::get(a_circle)->r = 
      std::to_string(radius);

    root->children.push_back(a_circle);
  }

  std::ofstream fout("test/general/10_circle.cpp.out.xml");
  fout << xml::declaration() << root->to_string();
}
