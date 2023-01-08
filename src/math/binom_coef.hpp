// [MATH_Header_Library]
//
#ifndef MATH_BINOM_COEF
#define MATH_BINOM_COEF

#include <type_traits>

namespace math {

template<typename _IntTp>
_IntTp binom_coef(_IntTp const &n, _IntTp const &k) {
  static_assert(std::is_integral<_IntTp>::value,
    "_IntTp in binom_coef<_IntTp> can only be integer type"
  );

  if (k == 0) {
    return 1;
  }

  if (k > n / 2) {
    return binom_coef(n, n - k);
  }

  _IntTp r = 1;
  for (_IntTp i = 1; i <= k; ++i) {
    r *= n - i + 1;
    r /= i;
  }

  return r;
}

} // namespace math

#endif // MATH_BINOM_COEF
