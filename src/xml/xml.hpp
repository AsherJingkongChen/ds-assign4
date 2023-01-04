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
//   [XML Format](https://developer.mozilla.org/en-US/docs/Web/XML)
//   [SVG Format](https://developer.mozilla.org/en-US/docs/Web/SVG)
//
#ifndef XML_XML
#define XML_XML

#include "element_circle.hpp"
#include "element_line.hpp"
#include "element_trait.hpp"
#include "element_rect.hpp"
#include "element_svg.hpp"
#include "element_text.hpp"

namespace xml {

namespace tag {

struct circle {};
struct line {};
struct rect {};
struct svg {};
struct text {};

} // namespace tag

// xml element builders and selectors
//   get() - build
//   get(e) - select
//
// usage:
//   auto e = xml::element< xml::tag::svg >::get();
//   xml::element< xml::tag::svg >(e)->version = "1.1";
//
template<typename _Tag> struct element;
template<> struct element<tag::circle>;
template<> struct element<tag::line>;
template<> struct element<tag::rect>;
template<> struct element<tag::svg>;
template<> struct element<tag::text>;

// XML document declaration
//
std::string declaration(
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


namespace xml {

template<>
struct element<tag::circle> {
  static element_trait_ptr get() {
    return 
      element_trait_ptr(
        std::make_shared<element_circle>()
      );
  }

  static element_circle_ptr get(element_trait_ptr const &p) {
    return
      std::dynamic_pointer_cast<
        element_circle_ptr::element_type
      >(p);
  }
};

template<>
struct element<tag::line> {
  static element_trait_ptr get() {
    return 
      element_trait_ptr(
        std::make_shared<element_line>()
      );
  }

  static element_line_ptr get(element_trait_ptr const &p) {
    return
      std::dynamic_pointer_cast<
        element_line_ptr::element_type
      >(p);
  }
};

template<>
struct element<tag::rect> {
  static element_trait_ptr get() {
    return 
      element_trait_ptr(
        std::make_shared<element_rect>()
      );
  }

  static element_rect_ptr get(element_trait_ptr const &p) {
    return
      std::dynamic_pointer_cast<
        element_rect_ptr::element_type
      >(p);
  }
};

template<>
struct element<tag::svg> {
  static element_trait_ptr get() {
    return 
      element_trait_ptr(
        std::make_shared<element_svg>()
      );
  }

  static element_svg_ptr get(element_trait_ptr const &p) {
    return
      std::dynamic_pointer_cast<
        element_svg_ptr::element_type
      >(p);
  }
};

template<>
struct element<tag::text> {
  static element_trait_ptr get() {
    return 
      element_trait_ptr(
        std::make_shared<element_text>()
      );
  }

  static element_text_ptr get(element_trait_ptr const &p) {
    return
      std::dynamic_pointer_cast<
        element_text_ptr::element_type
      >(p);
  }
};

} // namespace xml

#endif // XML_XML
