// [SVG_Header_Library]
//
#ifndef SVG_ELEMENT
#define SVG_ELEMENT

#include <string>
#include <vector>
#include <memory>

namespace svg {

class element {
public:
  typedef std::unique_ptr<element> element_ptr;

public:
  virtual int indent() const = 0;
  virtual bool is_self_closing() const = 0;
  virtual std::string tag() const = 0;
  virtual std::string attributes() const = 0;
  virtual std::vector<element_ptr> &children() = 0;
  virtual std::vector<const element_ptr> const &children() const = 0;

  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return _to_string(0);
  }

private:
  std::string _to_string(int indentation) const {
    std::string result(
      std::string(indentation, ' ') + 
      "<" + tag() + " " + attributes()
    );

    if (is_self_closing()) {
      return result + "/>\n";
    }

    result += ">\n";
    for (auto &e: children()) {
      result += e->_to_string(indentation + e->indent());
    }
    result +=
      std::string(indentation, ' ') + 
      "</" + tag() + ">\n";

    return result;
  }

public:
  virtual ~element() {}
};

} // namespace svg

#endif // SVG_ELEMENT
