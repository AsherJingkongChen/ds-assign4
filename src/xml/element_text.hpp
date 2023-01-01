// [XML_Header_Library]
//
#ifndef XML_ELEMENT_TEXT
#define XML_ELEMENT_TEXT

#include "element_trait.hpp"

namespace xml {

class element_text;
typedef std::shared_ptr<element_text> element_text_ptr;

class element_text: public element_trait {

public:
  attribute x;
  attribute y;
  attribute dx;
  attribute dy;
  attribute font_family;
  attribute font_size;
  attribute font_style; 
  attribute font_weight;
  attribute text_align;
  attribute text_anchor;

public:
  std::vector<attribute> attributes() const override {
    auto result = element_trait::attributes();
    result.insert(
      result.begin(), {
        x,
        y,
        dx,
        dy,
        font_family,
        font_size,
        font_style,
        font_weight,
        text_align,
        text_anchor
      }
    );
    return result;
  }

public:
  element_text():
    element_trait("text"),
    x("x"),
    y("y"),
    dx("dx"),
    dy("dy"),
    font_family("font-family"),
    font_size("font-size"),
    font_style("font-style"),
    font_weight("font-weight"),
    text_align("text-align"),
    text_anchor("text-anchor") {
  }

  element_text(element_text const &source):
    element_trait(source),
    x(source.x),
    y(source.y),
    dx(source.dx),
    dy(source.dy),
    font_family(source.font_family),
    font_size(source.font_size),
    font_style(source.font_style),
    font_weight(source.font_weight),
    text_align(source.text_align),
    text_anchor(source.text_anchor) {
  }

  element_text(element_text &&source) noexcept:
    element_trait(std::move(source)),
    x(std::move(source.x)),
    y(std::move(source.y)),
    dx(std::move(source.dx)),
    dy(std::move(source.dy)),
    font_family(std::move(source.font_family)),
    font_size(std::move(source.font_size)),
    font_style(std::move(source.font_style)),
    font_weight(std::move(source.font_weight)),
    text_align(std::move(source.text_align)),
    text_anchor(std::move(source.text_anchor)) {
  }

  element_text &operator=(element_text const &other) {
    element_trait::operator=(other);
    x = other.x;
    y = other.y;
    dx = other.dx;
    dy = other.dy;
    font_family = other.font_family;
    font_size = other.font_size;
    font_style = other.font_style;
    font_weight = other.font_weight;
    text_align = other.text_align;
    text_anchor = other.text_anchor;
    return *this;
  }

  element_text &operator=(element_text &&other) noexcept {
    element_trait::operator=(std::move(other));
    x = std::move(other.x);
    y = std::move(other.y);
    dx = std::move(other.dx);
    dy = std::move(other.dy);
    font_family = std::move(other.font_family);
    font_size = std::move(other.font_size);
    font_style = std::move(other.font_style);
    font_weight = std::move(other.font_weight);
    text_align = std::move(other.text_align);
    text_anchor = std::move(other.text_anchor);
    return *this;
  }
};

} // namespace xml

#endif // XML_ELEMENT_TEXT
