// [GEO_Header_Library]
//
// References:
// https://en.cppreference.com/w/cpp/numeric/complex
//
#ifndef GEO_VEC2
#define GEO_VEC2

#include <cmath>
#include <complex>
#include <string>

namespace geo {

typedef std::complex<float> vec2;

constexpr float pi_mul_2() {
  return M_PI * 2;
}

vec2 polar(float magnitude, float rotation) {
  return std::polar(magnitude, rotation * pi_mul_2());
}

float x(vec2 const &other) {
  return other.real();
}

float y(vec2 const &other) {
  return other.imag();
}

float &x(vec2 &other) {
  return reinterpret_cast<float(&)[2]>(other)[0];
}

float &y(vec2 &other) {
  return reinterpret_cast<float(&)[2]>(other)[1];
}

std::string x_str(vec2 const &other) {
  return std::to_string(other.real());
}

std::string y_str(vec2 const &other) {
  return std::to_string(other.imag());
}

} // namespace geo

#endif // GEO_VEC2
