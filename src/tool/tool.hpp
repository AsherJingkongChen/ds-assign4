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

#include "timer.hpp"

} // namespace tool

#endif // TOOL_TOOL
