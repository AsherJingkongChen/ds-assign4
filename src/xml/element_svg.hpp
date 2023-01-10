// [XML_Header_Library]
//
#ifndef XML_ELEMENT_SVG
#define XML_ELEMENT_SVG

#include "element_trait.hpp"

namespace xml {

namespace __detail {

class element_svg;
typedef std::shared_ptr<element_svg> element_svg_ptr;

class element_svg: public element_trait {

public:
  attribute width;
  attribute height;
  attribute version;
  attribute xmlns;

  attribute viewbox() const {
    if (width.empty() && height.empty()) {
      return attribute("viewBox");
    }
    return attribute(
      "viewBox", 
      "0 0 " + width.value + " " + height.value
    );
  }

public:
  std::vector<attribute> attributes() const override {
    auto result = element_trait::attributes();
    result.insert(
      result.begin(), {
        width,
        height,
        viewbox(),
        version,
        xmlns
      }
    );
    return result;
  }

public:
  element_svg():
      element_trait("svg"),
      width("width"),
      height("height"),
      version("version", "1.1"),
      xmlns("xmlns", "http://www.w3.org/2000/svg") {

    fill = "none";
    stroke = "black";
    stroke_linecap = "round";
  }

  element_svg(element_svg const &source):
    element_trait(source),
    width(source.width),
    height(source.height),
    version(source.version),
    xmlns(source.xmlns) {
  }

  element_svg(element_svg &&source) noexcept:
    element_trait(std::move(source)),
    width(std::move(source.width)),
    height(std::move(source.height)),
    version(std::move(source.version)),
    xmlns(std::move(source.xmlns)) {
  }

  element_svg &operator=(element_svg const &other) {
    element_trait::operator=(other);
    width = other.width;
    height = other.height;
    version = other.version;
    xmlns = other.xmlns;
    return *this;
  }

  element_svg &operator=(element_svg &&other) noexcept {
    element_trait::operator=(std::move(other));
    width = std::move(other.width);
    height = std::move(other.height);
    version = std::move(other.version);
    xmlns = std::move(other.xmlns);
    return *this;
  }
};

} // namespace __detail

} // namespace xml

#endif // XML_ELEMENT_SVG
