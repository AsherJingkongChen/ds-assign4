// [SVG_Header_Library]
//
#ifndef SVG_ELEMENT_SVG
#define SVG_ELEMENT_SVG

#include "element_policy.hpp"

namespace svg {

class element_svg: public element_policy {
public:
  std::vector<attribute> attributes() const override {
    return {
      width,
      height,
      version,
      xmlns
    };
  }

public:
  element_svg():
      element_policy(),
      width("width"),
      height("height"),
      version("version", "1.1"),
      xmlns("xmlns", "http://www.w3.org/2000/svg") {

    tag = "svg";
  }

public:
  attribute width;
  attribute height;
  attribute version;
  attribute xmlns;
};

} // namespace svg

#endif // SVG_ELEMENT_SVG
