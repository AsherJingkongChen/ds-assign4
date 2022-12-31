// [XML_Header_Library]
//
// MIT License
//
// Copyright (C) 2023 Asher Chen
// 
// Permission is hereby granted, free of charge, 
// to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), 
// to deal in the Software without restriction, 
// including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and 
// this permission notice shall be included 
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", 
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
// THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// References:
// https://developer.mozilla.org/en-US/docs/Web/XML
// https://developer.mozilla.org/en-US/docs/Web/SVG
//
#ifndef XML_XML
#define XML_XML

#include "element_policy.hpp"
#include "element_svg.hpp"

namespace xml {

namespace tag {
  struct svg {};
  struct line {};
}

// element builders and accessors
//
template<typename _Tag>
struct element {
};

template<>
struct element<tag::svg> {
  static element_policy_ptr get() {
    return element_policy_ptr(new element_svg);
  }
  
  static element_svg_ptr get(element_policy_ptr const &p) {
    return
      std::dynamic_pointer_cast<
        element_svg_ptr::element_type
      >(p);
  }
};

} // namespace xml


namespace xml {

std::string xml_declaration(
    std::string const &version = "1.0",
    std::string const &encoding = "UTF-8",
    std::string const &standalone = "no") {

  return
    "<?xml "
      "version=\"" + version + "\" "
      "encoding=\"" + encoding + "\" "
      "standalone=\"" + standalone + "\"?>\n";
}

} // namespace xml

#endif // XML_XML
