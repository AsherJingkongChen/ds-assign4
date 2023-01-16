// [TOOL_Header_Library]
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
//   [std::chrono](https://gcc.gnu.org/onlinedocs/gcc-12.2.0/libstdc++/api/a01672.html)
//
#ifndef TOOL_TOOL
#define TOOL_TOOL

#include <chrono>

namespace tool {

namespace unit {

typedef std::chrono::nanoseconds    nsec;
typedef std::chrono::microseconds   usec;
typedef std::chrono::milliseconds   msec;
typedef std::chrono::seconds        sec;
typedef std::chrono::minutes        min;
typedef std::chrono::hours          hour;

} // namespace unit

// dual-stated timer, is either paused or not paused
//
template<typename _Duration>
struct timer;

} // namespace tool

#include "timer.hpp"

#endif // TOOL_TOOL
