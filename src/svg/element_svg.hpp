// [SVG_Header_Library]
//
#ifndef SVG_ELEMENT_SVG
#define SVG_ELEMENT_SVG

#include "element.hpp"

namespace svg {

class element_svg: public element {
public:
  bool is_self_closing() const override {
    return false;
  }

  std::string tag() const override {
    return "svg";
  }

  std::string attributes() const override {
    return "width=\"200\" height=\"250\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"";
  }

  std::vector<element*> children() const override {
    return {};
  }

  int indent() const override {
    return 2;
  }
};

} // namespace svg

#endif // SVG_ELEMENT_SVG
