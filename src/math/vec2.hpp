// [MATH_Header_Library]
//
#ifndef MATH_VEC2
#define MATH_VEC2

#include <cmath>
#include <complex>
#include <numeric>
#include <string>

namespace math {

class vec2: public std::complex<float> {
public:
  constexpr float x() const {
    return this->real();
  }

  constexpr float y() const {
    return this->imag();
  }

  float &x() {
    return reinterpret_cast<float(&)[2]>(*this)[0];
  }

  float &y() {
    return reinterpret_cast<float(&)[2]>(*this)[1];
  }

  std::string x_str() const {
    return std::to_string(this->real());
  }

  std::string y_str() const {
    return std::to_string(this->imag());
  }

  using std::complex<float>::complex;

  constexpr vec2(std::complex<float> const &source):
    std::complex<float>(source) {
  }
};

constexpr float pi() {
  return M_PI;
}

// 1 rotation = 2 PI radians
//
vec2 polar(float magnitude, float rotation) {
  return std::polar(magnitude, rotation * 2 * pi());
}

} // namespace math

#endif // MATH_VEC2
