#ifndef __STAN__MATH__FUNCTIONS__BINOMIAL_COEFFICIENT_LOG_HPP__
#define __STAN__MATH__FUNCTIONS__BINOMIAL_COEFFICIENT_LOG_HPP__

#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/tools/promotion.hpp>

namespace stan {

  namespace math {

    /**
     * Return the log of the binomial coefficient for the specified
     * arguments.
     *
     * The binomial coefficient, \f${N \choose n}\f$, read "N choose n", is
     * defined for \f$0 \leq n \leq N\f$ by
     *
     * \f${N \choose n} = \frac{N!}{n! (N-n)!}\f$.
     *
     * This function uses Gamma functions to define the log
     * and generalize the arguments to continuous N and n.
     *
     * \f$ \log {N \choose n} = \log \ \Gamma(N+1) - \log \Gamma(n+1) - \log \Gamma(N-n+1)\f$.
     *
     * @param N total number of objects.
     * @param n number of objects chosen.
     * @return log (N choose n).
     */
    template <typename T_N, typename T_n>
    inline typename boost::math::tools::promote_args<T_N, T_n>::type
    binomial_coefficient_log(const T_N N, const T_n n) {
      using std::log;
      using boost::math::lgamma;

      const double cutoff = 1000;
      if ((N < cutoff) || (N - n < cutoff)) {
        return lgamma(N + 1.0) - lgamma(n + 1.0) - lgamma(N - n + 1.0);
      } else {
        return n * log(N - n) + (N + 0.5) * log(N/(N-n))
          + 1/(12*N) - n - 1/(12*(N-n)) - lgamma(n + 1.0);
      }
    }

  }
}

#endif
