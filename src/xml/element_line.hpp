// [XML_Header_Library]
//
#ifndef XML_ELEMENT_LINE
#define XML_ELEMENT_LINE

#include "element_policy.hpp"

namespace xml {

class element_line;
typedef std::shared_ptr<element_line> element_line_ptr;

class element_line: public element_policy {
public:
  attribute x1;
  attribute x2;
  attribute y1;
  attribute y2;

public:
  std::vector<attribute> attributes() const override {
    return {
      x1,
      x2,
      y1,
      y2
    };
  }

public:
  element_line():
      element_policy(),
      x1("x1"),
      x2("x2"),
      y1("y1"),
      y2("y2") {

    tag = "line";
  }

  element_line(element_line const &source):
    element_policy(source),
    x1(source.x1),
    x2(source.x2),
    y1(source.y1),
    y2(source.y2) {
  }

  element_line(element_line &&source) noexcept:
    element_policy(std::move(source)),
    x1(std::move(source.x1)),
    x2(std::move(source.x2)),
    y1(std::move(source.y1)),
    y2(std::move(source.y2)) {
  }

  element_line &operator=(element_line const &other) {
    element_policy::operator=(other);
    x1 = other.x1;
    x2 = other.x2;
    y1 = other.y1;
    y2 = other.y2;
    return *this;
  }

  element_line &operator=(element_line &&other) noexcept {
    element_policy::operator=(std::move(other));
    x1 = std::move(other.x1);
    x2 = std::move(other.x2);
    y1 = std::move(other.y1);
    y2 = std::move(other.y2);
    return *this;
  }
};

} // namespace xml

#endif // XML_ELEMENT_LINE
