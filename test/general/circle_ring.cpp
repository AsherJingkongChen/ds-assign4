#include "../../src/geo/geo.hpp"
#include "../../src/xml/xml.hpp"
#include <fstream>

using namespace xml::tag;

int main() {
  auto root = xml::element<svg>::get();
  const auto count = 1000;
  const auto sidelen_2 = 1000.0F;
  const auto radius = sidelen_2 / count;
  const auto stroke_width = radius / 10.0F;
  const auto yx_ratio = 0.4F;
  const auto center = geo::vec2(sidelen_2, sidelen_2 * yx_ratio);

  xml::element<svg>::get(root)->width = 
    std::to_string(geo::x(center) * 2.0F);
  xml::element<svg>::get(root)->height = 
    std::to_string(geo::y(center) * 2.0F);

  root->fill = "white";
  root->stroke_width = std::to_string(stroke_width);

  // lines
  //
  for (int i = 0; i < count; i++) {
    auto a_line = xml::element<line>::get();

    geo::vec2 a_line_p[2] = {
      center +
      geo::polar(
        sidelen_2 - radius - stroke_width,
        i / float(count)
      ),
      center +
      geo::polar(
        sidelen_2 - radius - stroke_width,
        (i + 1) / float(count)
      )
    };

    geo::y(a_line_p[0]) = 
      geo::y(center) + 
      yx_ratio * (geo::y(a_line_p[0]) - geo::y(center));

    geo::y(a_line_p[1]) = 
      geo::y(center) + 
      yx_ratio * (geo::y(a_line_p[1]) - geo::y(center));

    xml::element<line>::get(a_line)->x1 = geo::x_str(a_line_p[0]);
    xml::element<line>::get(a_line)->x2 = geo::x_str(a_line_p[1]);
    xml::element<line>::get(a_line)->y1 = geo::y_str(a_line_p[0]);
    xml::element<line>::get(a_line)->y2 = geo::y_str(a_line_p[1]);

    root->children.push_back(a_line);
  }

  // circles
  //
  for (int i = 0; i < count; i++) {
    auto a_circle = xml::element<circle>::get();

    auto a_circle_p = 
      center +
      geo::polar(
        sidelen_2 - radius - stroke_width,
        i / float(count)
      );

    geo::y(a_circle_p) = 
      geo::y(center) + 
      yx_ratio * (geo::y(a_circle_p) - geo::y(center));

    xml::element<circle>::get(a_circle)->cx = geo::x_str(a_circle_p);
    xml::element<circle>::get(a_circle)->cy = geo::y_str(a_circle_p);
    xml::element<circle>::get(a_circle)->r = std::to_string(radius);

    root->children.push_back(a_circle);
  }

  // texts
  //
  for (int i = 0; i < count; i++) {
    auto a_text = xml::element<text>::get();

    auto a_text_p = 
      center +
      geo::polar(
        sidelen_2 - radius - stroke_width,
        i / float(count)
      );

    geo::y(a_text_p) = 
      geo::y(center) + 
      yx_ratio * (geo::y(a_text_p) - geo::y(center));

    xml::element<text>::get(a_text)->x = geo::x_str(a_text_p);
    xml::element<text>::get(a_text)->y = geo::y_str(a_text_p);
    xml::element<text>::get(a_text)->font_size = std::to_string(radius / 1.6F);
    xml::element<text>::get(a_text)->font_family = "monospace";
    xml::element<text>::get(a_text)->font_weight = "bold";
    xml::element<text>::get(a_text)->text_anchor = "middle";

    a_text->fill = "black";
    a_text->stroke_width = "0";
    a_text->text = std::to_string(i + 1);

    root->children.push_back(a_text);
  }


  std::ofstream fout("test/general/circle_ring.out.svg");
  fout << xml::declaration() << root->to_string();
}
