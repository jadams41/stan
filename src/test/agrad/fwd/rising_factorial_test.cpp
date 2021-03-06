#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, rising_factorial) {
  using stan::agrad::fvar;
  using stan::agrad::rising_factorial;
  using boost::math::digamma;

  fvar<double> a(4.0,1.0);
  fvar<double> x = rising_factorial(a,1);
  EXPECT_FLOAT_EQ(4.0, x.val_);
  EXPECT_FLOAT_EQ(1.0, x.d_);

  fvar<double> c(-3.0,2.0);

  EXPECT_THROW(rising_factorial(c, 2), std::domain_error);
  EXPECT_THROW(rising_factorial(2, c), std::domain_error);
  EXPECT_THROW(rising_factorial(c, c), std::domain_error);

  x = rising_factorial(a,a);
  EXPECT_FLOAT_EQ(840.0, x.val_);
  EXPECT_FLOAT_EQ(840.0 * (2 * digamma(8) - digamma(4)), x.d_);

  x = rising_factorial(5, a);
  EXPECT_FLOAT_EQ(1680.0, x.val_);
  EXPECT_FLOAT_EQ(1680.0 * digamma(9), x.d_);
}
//WONT WORK UNTIL STUFF IN CLEAN_UP_FVAR IS MERGED IN -- REQUIRES DIGAMMA FUNCTION
// TEST(AgradFvarVar, rising_factorial) {
//   using stan::agrad::fvar;
//   using stan::agrad::var;
//   using stan::agrad::rising_factorial;

//   fvar<var> a(4.0,1.0);
//   fvar<var> b(4.0,1.0);
//   fvar<var> c = rising_factorial(a,b);

//   EXPECT_FLOAT_EQ((840.0), c.val_.val());
//   EXPECT_FLOAT_EQ(840. * (2 * digamma(8) - digamma(4)), c.d_.val());

//   AVEC y = createAVEC(a.val_,b.val_);
//   VEC g;
//   c.val_.grad(y,g);
//   EXPECT_FLOAT_EQ(0, g[0]);
//   EXPECT_FLOAT_EQ(0, g[1]);
// }

// TEST(AgradFvarFvar, rising_factorial) {
//   using stan::agrad::fvar;
//   using stan::math::rising_factorial;

//   fvar<fvar<double> > x;
//   x.val_.val_ = 4.0;
//   x.val_.d_ = 1.0;

//   fvar<fvar<double> > y;
//   y.val_.val_ = 4.0;
//   y.d_.val_ = 1.0;

//   fvar<fvar<double> > a = rising_factorial(x,y);

//   EXPECT_FLOAT_EQ((840.0), a.val_.val_);
//   EXPECT_FLOAT_EQ(0, a.val_.d_);
//   EXPECT_FLOAT_EQ(0, a.d_.val_);
//   EXPECT_FLOAT_EQ(0, a.d_.d_);
// }
