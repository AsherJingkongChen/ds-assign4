#ifndef SVG_ATTRIBUTE
#define SVG_ATTRIBUTE

#include <string>

namespace svg {

class attribute {
public:
  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return key + "=\"" + value + "\"";
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

} // namespace svg

#endif // SVG_ATTRIBUTE
