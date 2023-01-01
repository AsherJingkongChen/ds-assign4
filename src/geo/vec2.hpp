// [GEO_Header_Library]
//
#ifndef GEO_VEC2
#define GEO_VEC2

#include <utility>
#include <numeric>
#include <cmath>

namespace geo {

struct vec2 {
public:
  float x;
  float y;

public:
  vec2 operator+(vec2 const &other) const {
    return {x + other.x, y + other.y};
  }

  vec2 &operator+=(vec2 const &other) {
    return *this = (*this + other);
  }

  vec2 operator-() const {
    return {-x, -y};
  }

  vec2 operator-(vec2 const &other) const {
    return *this + (-other);
  }

  vec2 &operator-=(vec2 const &other) {
    return *this = (*this - other);
  }

  vec2 operator+(float rad) const {
    return {
      x * std::cos(rad) - y * std::sin(rad),
      x * std::sin(rad) + y * std::cos(rad),
    };
  }

  vec2 &operator+=(float rad) {
    return *this = (*this + rad);
  }

  vec2 operator-(float rad) const {
    return *this + (-rad);
  }

  vec2 &operator-=(float rad) {
    return *this = (*this - rad);
  }

  vec2 rotated(vec2 const &anchor, float rad) const {
    return anchor + ((*this - anchor) + rad);
  }

  vec2 &rotate(vec2 const &anchor, float rad) {
    return *this = rotated(anchor, rad);
  }

public:
  vec2():
    x(),
    y() {
  }

  vec2(float x, float y):
    x(x),
    y(y) {
  }

  vec2(vec2 const &source):
    x(source.x),
    y(source.y) {
  }

  vec2 &operator=(vec2 const &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
};

} // namespace geo

#endif // GEO_VEC2
