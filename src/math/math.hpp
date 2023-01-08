// [MATH_Header_Library]
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
//   [std::complex](https://gcc.gnu.org/onlinedocs/gcc-12.2.0/libstdc++/api/a01572.html)
//
#ifndef MATH_MATH
#define MATH_MATH

#include <type_traits>

namespace math {

// pi with float type
//
constexpr float pi();

// vec2:
//   x - real part
//   y - imaginary part
//
// specialized std::complex<float>
//
class vec2;

// specialized std::polar that returns vec2
//
// note:
//   1 rotation = 2 PI radians
//
vec2 polar(float magnitude, float rotation);

// binomial coefficient
// binom_coef(n, k) == n! / (k! * (n - k)!)
//
// References:
//   https://stackoverflow.com/a/42285958
//
template<typename _IntTp>
_IntTp binom_coef(_IntTp const &n, _IntTp const &k);

} // namespace math

#include "vec2.hpp"
#include "binom_coef.hpp"

#endif // MATH_MATH
