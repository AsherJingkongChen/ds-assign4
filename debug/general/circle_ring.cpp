#include "../../src/math/math.hpp"
#include "../../src/xml/xml.hpp"
#include <fstream>

using namespace xml::tag;

int main() {
  auto root = xml::element<svg>::get();
  const auto count = 1000;
  const auto sidelen_2 = 1000.0F;
  const auto radius = sidelen_2 / count;
  const auto stroke_width = radius / 10.0F;
  const auto yx_ratio = 0.5F;
  const auto center = math::vec2(sidelen_2, sidelen_2 * yx_ratio);

  xml::element<svg>::get(root)->width = 
    std::to_string(center.x() * 2.0F);
  xml::element<svg>::get(root)->height = 
    std::to_string(center.y() * 2.0F);

  root->fill = "white";
  root->stroke_width = std::to_string(stroke_width);

  // lines
  //
  for (int i = 0; i < count; i++) {
    auto a_line = xml::element<line>::get();

    math::vec2 a_line_p[2] = {
      center +
      math::polar(
        sidelen_2 - radius - stroke_width,
        i / float(count)
      ),
      center +
      math::polar(
        sidelen_2 - radius - stroke_width,
        (i + 1) / float(count)
      )
    };

    a_line_p[0].y() = 
      center.y() + 
      yx_ratio * (a_line_p[0].y() - center.y());

    a_line_p[1].y() = 
      center.y() + 
      yx_ratio * (a_line_p[1].y() - center.y());

    xml::element<line>::get(a_line)->x1 = a_line_p[0].x_str();
    xml::element<line>::get(a_line)->x2 = a_line_p[1].x_str();
    xml::element<line>::get(a_line)->y1 = a_line_p[0].y_str();
    xml::element<line>::get(a_line)->y2 = a_line_p[1].y_str();

    root->children.push_back(a_line);
  }

  // circles
  //
  for (int i = 0; i < count; i++) {
    auto a_circle = xml::element<circle>::get();

    math::vec2 a_circle_p = 
      center +
      math::polar(
        sidelen_2 - radius - stroke_width,
        i / float(count)
      );

    a_circle_p.y() = 
      center.y() + 
      yx_ratio * (a_circle_p.y() - center.y());

    xml::element<circle>::get(a_circle)->cx = a_circle_p.x_str();
    xml::element<circle>::get(a_circle)->cy = a_circle_p.y_str();
    xml::element<circle>::get(a_circle)->r = std::to_string(radius);

    root->children.push_back(a_circle);
  }

  // texts
  //
  for (int i = 0; i < count; i++) {
    auto a_text = xml::element<text>::get();

    math::vec2 a_text_p = 
      center +
      math::polar(
        sidelen_2 - radius - stroke_width,
        i / float(count)
      );

    a_text_p.y() = 
      center.y() +
      yx_ratio * (a_text_p.y() - center.y());

    xml::element<text>::get(a_text)->x = a_text_p.x_str();
    xml::element<text>::get(a_text)->y = a_text_p.y_str();
    xml::element<text>::get(a_text)->font_size = std::to_string(radius / 1.6F);
    xml::element<text>::get(a_text)->font_family = "monospace";
    xml::element<text>::get(a_text)->font_weight = "bold";
    xml::element<text>::get(a_text)->text_anchor = "middle";

    a_text->fill = "black";
    a_text->stroke_width = "0";
    a_text->text = std::to_string(i + 1);

    root->children.push_back(a_text);
  }

  std::ofstream fout("debug/general/circle_ring.out.svg");
  fout << xml::declaration() << root->to_string();
}
