#include "../../src/xml/xml.hpp"
#include <fstream>

using namespace xml::tag;

int main() {
  auto svg1 = xml::element<svg>::get();
  auto circle1 = xml::element<circle>::get();
  auto circle2 = xml::element<circle>::get();
  auto line1 = xml::element<line>::get();

  auto circle1_ref = xml::element<circle>::get(circle1);
  circle1_ref->cx = "20";
  circle1_ref->cy = "20";
  circle1_ref->r  = "10";

  auto circle2_ref = xml::element<circle>::get(circle2);
  circle2_ref->cx = "80";
  circle2_ref->cy = "80";
  circle2_ref->r  = "10";

  auto line1_ref = xml::element<line>::get(line1);
  line1_ref->x1 = "20";
  line1_ref->x2 = "80";
  line1_ref->y1 = "20";
  line1_ref->y2 = "80";

  svg1->children.insert(
    svg1->children.end(), {
      circle1, 
      circle2, 
      line1
    }
  );

  svg1->text = "hello world!\n";

  std::ofstream fout("debug/xml/2_circle_and_1_line.svg.log");
  fout << xml::declaration() << std::string(*svg1);
}