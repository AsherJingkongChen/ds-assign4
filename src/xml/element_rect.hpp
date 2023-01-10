// [XML_Header_Library]
//
#ifndef XML_ELEMENT_RECT
#define XML_ELEMENT_RECT

#include "element_trait.hpp"

namespace xml {

namespace __detail {

class element_rect;
typedef std::shared_ptr<element_rect> element_rect_ptr;

class element_rect: public element_trait {

public:
  attribute x;
  attribute y;
  attribute rx;
  attribute ry;
  attribute height;
  attribute width;

public:
  std::vector<attribute> attributes() const override {
    auto result = element_trait::attributes();
    result.insert(
      result.begin(), {
        x,
        y,
        rx,
        ry,
        height,
        width
      }
    );
    return result;
  }

public:
  element_rect():
    element_trait("rect"),
    x("x"),
    y("y"),
    rx("rx"),
    ry("ry"),
    height("height"),
    width("width") {
  }

  element_rect(element_rect const &source):
    element_trait(source),
    x(source.x),
    y(source.y),
    rx(source.rx),
    ry(source.ry),
    height(source.height),
    width(source.width) {
  }

  element_rect(element_rect &&source) noexcept:
    element_trait(std::move(source)),
    x(std::move(source.x)),
    y(std::move(source.y)),
    rx(std::move(source.rx)),
    ry(std::move(source.ry)),
    height(std::move(source.height)),
    width(std::move(source.width)) {
  }

  element_rect &operator=(element_rect const &other) {
    element_trait::operator=(other);
    x = other.x;
    y = other.y;
    rx = other.rx;
    ry = other.ry;
    height = other.height;
    width = other.width;
    return *this;
  }

  element_rect &operator=(element_rect &&other) noexcept {
    element_trait::operator=(std::move(other));
    x = std::move(other.x);
    y = std::move(other.y);
    rx = std::move(other.rx);
    ry = std::move(other.ry);
    height = std::move(other.height);
    width = std::move(other.width);
    return *this;
  }
};

} // namespace __detail

} // namespace xml

#endif // XML_ELEMENT_RECT
