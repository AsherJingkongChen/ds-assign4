// [XML_Header_Library]
//
#ifndef XML_ELEMENT_SVG
#define XML_ELEMENT_SVG

#include "element_policy.hpp"

namespace xml {

class element_svg;
typedef std::shared_ptr<element_svg> element_svg_ptr;

class element_svg: public element_policy {
public:
  attribute width;
  attribute height;
  attribute version;
  attribute xmlns;

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

  element_svg(element_svg const &source):
    element_policy(source),
    width(source.width),
    height(source.height),
    version(source.version),
    xmlns(source.xmlns) {
  }

  element_svg(element_svg &&source) noexcept:
    element_policy(std::move(source)),
    width(std::move(source.width)),
    height(std::move(source.height)),
    version(std::move(source.version)),
    xmlns(std::move(source.xmlns)) {
  }

  element_svg &operator=(element_svg const &other) {
    element_policy::operator=(other);
    width = other.width;
    height = other.height;
    version = other.version;
    xmlns = other.xmlns;
    return *this;
  }

  element_svg &operator=(element_svg &&other) noexcept {
    element_policy::operator=(std::move(other));
    width = std::move(other.width);
    height = std::move(other.height);
    version = std::move(other.version);
    xmlns = std::move(other.xmlns);
    return *this;
  }
};

} // namespace xml

#endif // XML_ELEMENT_SVG
