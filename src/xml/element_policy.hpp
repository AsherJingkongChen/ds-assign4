// [XML_Header_Library]
//
#ifndef XML_ELEMENT_POLICY
#define XML_ELEMENT_POLICY

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "attribute.hpp"

namespace xml {

static inline int xml_indent = 2;

class element_policy;
typedef std::shared_ptr<element_policy> element_policy_ptr;

class element_policy {
public:
  virtual std::vector<attribute> attributes() const {
    return {};
  }

  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return _to_string(0);
  }

private:
  bool is_self_closing() const {
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
      result += " " + a.to_string();
    }

    if (is_self_closing()) {
      return result + "/>\n";
    }

    result += 
      ">\n" + 
      std::string(indent + xml_indent, ' ') + 
      text + "\n";
    
    for (auto &e: children) {
      result += e->_to_string(indent + xml_indent);
    }

    result +=
      std::string(indent, ' ') + 
      "</" + tag + ">\n";

    return result;
  }

public:
  virtual ~element_policy() {
  }

  element_policy():
    tag(),
    text(),
    children() {
  }

  element_policy(element_policy const &source):
    tag(source.tag),
    text(source.text),
    children(source.children) {
  }

  element_policy(element_policy &&source) noexcept:
    tag(std::move(source.tag)),
    text(std::move(source.text)),
    children(std::move(source.children)) {
  }

  element_policy &operator=(element_policy const &other) {
    tag = other.tag;
    text = other.text;
    children = other.children;
    return *this;
  }

  element_policy &operator=(element_policy &&other) noexcept {
    tag = std::move(other.tag);
    text = std::move(other.text);
    children = std::move(other.children);
    return *this;
  }

public:
  std::string tag;
  std::string text;
  std::vector<element_policy_ptr> children;
};

} // namespace xml

#endif // XML_ELEMENT_POLICY
