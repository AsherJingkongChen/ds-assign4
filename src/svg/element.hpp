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
  typedef std::unique_ptr<element> object_type;

public:
  virtual int indent() const = 0;
  virtual bool is_self_closing() const = 0;
  virtual std::string tag() const = 0;
  virtual std::string attributes() const = 0; // TODO: std::vector<attribute_pair>
  virtual std::string &text() = 0;
  virtual std::string const &text() const = 0;
  virtual std::vector<object_type> &children() = 0;
  virtual std::vector<object_type> const &children() const = 0;

  operator std::string() const {
    return to_string();
  }

  std::string to_string() const {
    return _to_string(-indent());
  }

private:
  std::string _to_string(int base_indent) const {
    base_indent += indent();

    std::string result(
      std::string(base_indent, ' ') + 
      "<" + tag() + " " + attributes()
    );

    if (is_self_closing()) {
      return result + "/>\n";
    }

    result += 
      ">\n" + 
      std::string(base_indent, ' ') + 
      text() + "\n";
    
    for (auto &e: children()) {
      result += e->_to_string(base_indent);
    }
    result +=
      std::string(base_indent, ' ') + 
      "</" + tag() + ">\n";

    return result;
  }

public:
  virtual ~element() {}
};

} // namespace svg

#endif // SVG_ELEMENT
