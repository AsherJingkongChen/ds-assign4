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
  typedef std::complex<float> base_type;

public:
  constexpr float x() const {
    return base_type::real();
  }

  constexpr float y() const {
    return base_type::imag();
  }

  float &x() {
    return reinterpret_cast<float(&)[2]>(*this)[0];
  }

  float &y() {
    return reinterpret_cast<float(&)[2]>(*this)[1];
  }

  std::string x_str() const {
    return std::to_string(base_type::real());
  }

  std::string y_str() const {
    return std::to_string(base_type::imag());
  }

  using base_type::base_type;

  constexpr vec2(base_type const &source):
    base_type(source) {
  }
};

constexpr float pi() {
  return M_PI;
}

vec2 polar(float magnitude, float rotation) {
  return std::polar(magnitude, rotation * 2 * pi());
}

} // namespace math

#endif // MATH_VEC2
