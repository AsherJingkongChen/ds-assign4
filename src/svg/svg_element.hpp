// [SVG_Header_Library]
//
#ifndef SVG_SVG_ELEMENT
#define SVG_SVG_ELEMENT

#include "element_policy.hpp"

namespace svg {

class svg_element: public element_policy {
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

#endif // SVG_SVG_ELEMENT
