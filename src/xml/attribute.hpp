// [XML_Header_Library]
//
#ifndef XML_ATTRIBUTE
#define XML_ATTRIBUTE

#include <string>

namespace xml {

class attribute {
public:
  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return key + "=\"" + value + "\"";
  }

  attribute &operator=(std::string const &value) {
    this->value = value;
    return *this;
  }

  attribute &operator=(std::string &&value) noexcept {
    this->value = std::move(value);
    return *this;
  }

public:
  attribute(
    std::string const &key):

    key(key),
    value() {
  }

  attribute(
    std::string const &key, 
    std::string const &value):

    key(key),
    value(value) {
  }

  attribute(attribute const &source):
    key(source.key),
    value(source.value) {
  }

  attribute(attribute &&source) noexcept:
    key(std::move(source.key)),
    value(std::move(source.value)) {
  }

  attribute &operator=(attribute const &other) {
    key = other.key;
    value = other.value;
    return *this;
  }

  attribute &operator=(attribute &&other) noexcept {
    key = std::move(other.key);
    value = std::move(other.value);
    return *this;
  }

public:
  std::string key;
  std::string value;
};

} // namespace xml

#endif // XML_ATTRIBUTE
