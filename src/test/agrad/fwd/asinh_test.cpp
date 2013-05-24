#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, asinh) {
  using stan::agrad::fvar;
  using boost::math::asinh;
  using std::sqrt;

  fvar<double> x(0.5);
  x.d_ = 1.0;

  fvar<double> a = asinh(x);
  EXPECT_FLOAT_EQ(asinh(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 / sqrt(1 + (0.5) * (0.5)), a.d_);

  fvar<double> y(-1.2);
  y.d_ = 1.0;

  fvar<double> b = asinh(y);
  EXPECT_FLOAT_EQ(asinh(-1.2), b.val_);
  EXPECT_FLOAT_EQ(1 / sqrt(1 + (-1.2) * (-1.2)), b.d_);

  fvar<double> c = asinh(-x);
  EXPECT_FLOAT_EQ(asinh(-0.5), c.val_);
  EXPECT_FLOAT_EQ(-1 / sqrt(1 + (-0.5) * (-0.5)), c.d_);
}

TEST(AgradFvarVar, asinh) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using boost::math::asinh;

  fvar<var> x;
  x.val_ = 1.5;
  x.d_ = 1.3;
  fvar<var> a = asinh(x);

  EXPECT_FLOAT_EQ(asinh(1.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 / sqrt(1.0 + 1.5 * 1.5), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(1.0 / sqrt(1.0 + 1.5 * 1.5), g[0]);

  y = createAVEC(x.d_);
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(0, g[0]);
}

TEST(AgradFvarFvar, asinh) {
  using stan::agrad::fvar;
  using boost::math::asinh;

  fvar<fvar<double> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 2.0;
  x.d_.val_ = 3.0;
  x.d_.d_ = 4.0;

  fvar<fvar<double> > a = asinh(x);

  EXPECT_FLOAT_EQ(asinh(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(2.0 / sqrt(1.0 + 1.5 * 1.5), a.val_.d_);
  EXPECT_FLOAT_EQ(3.0 / sqrt(1.0 + 1.5 * 1.5), a.d_.val_);
  //EXPECT_FLOAT_EQ(1.2 / sqrt(1.0 + 1.5 * 1.5), a.d_.d_);
}
