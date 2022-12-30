// [SVG_Header_Library]
//
#ifndef SVG_ELEMENT_POLICY
#define SVG_ELEMENT_POLICY

#include <string>
#include <vector>
#include <memory>
#include "attribute.hpp"

namespace svg {

class element_policy;

typedef std::shared_ptr<element_policy> element_ptr;

class element_policy {
public:
  virtual std::vector<attribute> attributes() const = 0;

  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return _to_string(-indent);
  }

private:
  bool is_self_closing() const {
    return
      text.empty() &&
      children.empty();
  }

  std::string _to_string(int base_indent) const {
    base_indent += indent;

    std::string result(
      std::string(base_indent, ' ') + 
      "<" + tag
    );

    for (auto &a: attributes()) {
      result += " " + a.to_string();
    }

    if (is_self_closing()) {
      return result + "/>\n";
    }

    result += 
      ">\n" + 
      std::string(base_indent, ' ') + 
      text + "\n";
    
    for (auto &e: children) {
      result += e->_to_string(base_indent);
    }
    result +=
      std::string(base_indent, ' ') + 
      "</" + tag + ">\n";

    return result;
  }

public:
  virtual ~element_policy() {}

  element_policy():
    tag(),
    text(),
    children(),
    indent(2) {
  }

  element_policy(element_policy const &source):
    tag(source.tag),
    text(source.text),
    children(source.children),
    indent(source.indent) {
  }

  element_policy(element_policy &&source) noexcept:
    tag(std::move(source.tag)),
    text(std::move(source.text)),
    children(std::move(source.children)),
    indent(std::move(source.indent)) {
  }

  element_policy &operator=(element_policy const &other) {
    tag = other.tag;
    text = other.text;
    children = other.children;
    indent = other.indent;
    return *this;
  }

  element_policy &operator=(element_policy &&other) noexcept {
    tag = std::move(other.tag);
    text = std::move(other.text);
    children = std::move(other.children);
    indent = std::move(other.indent);
    return *this;
  }

public:
  std::string tag;
  std::string text;
  std::vector<element_ptr> children;
  int indent;
};

} // namespace svg

#endif // SVG_ELEMENT_POLICY
