// [SVG_Header_Library]
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
// SVG Format is referenced from:
// https://developer.mozilla.org/en-US/docs/Web/SVG
//
#ifndef SVG_SVG
#define SVG_SVG

#include "element_policy.hpp"
#include "svg_element.hpp"

namespace svg {

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

} // namespace svg

#endif // SVG_SVG
