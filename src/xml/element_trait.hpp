// [XML_Header_Library]
//
#ifndef XML_ELEMENT_TRAIT
#define XML_ELEMENT_TRAIT

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "attribute.hpp"

namespace xml {

static inline int indent = 2;

class element_trait;
typedef std::shared_ptr<element_trait> element_trait_ptr;

class element_trait {
private:
  std::string tag;

public:
  std::string text;
  std::vector<element_trait_ptr> children;
  attribute fill;
  attribute stroke;
  attribute stroke_linecap;
  attribute stroke_width;

public:
  virtual std::vector<attribute> attributes() const {
    return {
      fill,
      stroke,
      stroke_linecap,
      stroke_width
    };
  }

  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return _to_string(0);
  }

private:
  bool self_closing() const {
    return
      text.empty() &&
      children.empty();
  }

  std::string _to_string(int indent) const {
    std::string result(
      std::string(indent, ' ') + 
      "<" + tag
    );

    for (auto &a: attributes()) {
      if (not a.empty()) {
        result += " " + a.to_string();
      }
    }

    if (self_closing()) {
      return result + "/>\n";
    }

    result += ">\n";

    if (not text.empty()) {
      result += 
        std::string(indent + xml::indent, ' ') +
        text + "\n";
    }
    
    for (auto &e: children) {
      result += e->_to_string(indent + xml::indent);
    }

    result +=
      std::string(indent, ' ') + 
      "</" + tag + ">\n";

    return result;
  }

public:
  virtual ~element_trait() {
  }

  element_trait(std::string const &tag):
    tag(tag),
    text(),
    children(),
    fill("fill"),
    stroke("stroke"),
    stroke_linecap("stroke-linecap"),
    stroke_width("stroke-width") {
  }

  element_trait(element_trait const &source):
    tag(source.tag),
    text(source.text),
    children(source.children),
    fill(source.fill),
    stroke(source.stroke),
    stroke_linecap(source.stroke_linecap),
    stroke_width(source.stroke_width) {
  }

  element_trait(element_trait &&source) noexcept:
    tag(std::move(source.tag)),
    text(std::move(source.text)),
    children(std::move(source.children)),
    fill(std::move(source.fill)),
    stroke(std::move(source.stroke)),
    stroke_linecap(std::move(source.stroke_linecap)),
    stroke_width(std::move(source.stroke_width)) {
  }

  element_trait &operator=(element_trait const &other) {
    tag = other.tag;
    text = other.text;
    children = other.children;
    fill = other.fill;
    stroke = other.stroke;
    stroke_linecap = other.stroke_linecap;
    stroke_width = other.stroke_width;
    return *this;
  }

  element_trait &operator=(element_trait &&other) noexcept {
    tag = std::move(other.tag);
    text = std::move(other.text);
    children = std::move(other.children);
    fill = std::move(other.fill);
    stroke = std::move(other.stroke);
    stroke_linecap = std::move(other.stroke_linecap);
    stroke_width = std::move(other.stroke_width);
    return *this;
  }
};

} // namespace xml

#endif // XML_ELEMENT_TRAIT
