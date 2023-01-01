// [XML_Header_Library]
//
#ifndef XML_ELEMENT_CIRCLE
#define XML_ELEMENT_CIRCLE

#include "element_trait.hpp"

namespace xml {

class element_circle;
typedef std::shared_ptr<element_circle> element_circle_ptr;

class element_circle: public element_trait {
public:
  attribute cx;
  attribute cy;
  attribute r;

public:
  std::vector<attribute> attributes() const override {
    auto result = element_trait::attributes();
    result.insert(
      result.begin(), {
        cx,
        cy,
        r
      }
    );
    return result;
  }

public:
  element_circle():
    element_trait("circle"),
    cx("cx"),
    cy("cy"),
    r("r") {
  }

  element_circle(element_circle const &source):
    element_trait(source),
    cx(source.cx),
    cy(source.cy),
    r(source.r) {
  }

  element_circle(element_circle &&source) noexcept:
    element_trait(std::move(source)),
    cx(std::move(source.cx)),
    cy(std::move(source.cy)),
    r(std::move(source.r)) {
  }

  element_circle &operator=(element_circle const &other) {
    element_trait::operator=(other);
    cx = other.cx;
    cy = other.cy;
    r = other.r;
    return *this;
  }

  element_circle &operator=(element_circle &&other) noexcept {
    element_trait::operator=(std::move(other));
    cx = std::move(other.cx);
    cy = std::move(other.cy);
    r = std::move(other.r);
    return *this;
  }
};

} // namespace xml

#endif // XML_ELEMENT_CIRCLE
