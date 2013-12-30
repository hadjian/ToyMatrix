#include <Include/arithmeticex.h>

#include <gtest/gtest.h>

#include <cstdio>
using namespace std;

TEST(ArithmeticExceptions, IntRangeCheck) {
  // 0, -1 and 1 as the intervall boundaries.
  multRangeCheck<int>(1000, 0);
  multRangeCheck<int>(-1000, -1);
  multRangeCheck<int>(-1000, 1);
  multRangeCheck<int>(1, 2147483647);
  multRangeCheck<int>(-1, -2147483647);
  multRangeCheck<int>(1, -2147483648);
  multRangeCheck<int>(-1, 2147483648);

  // Overstep minimum and maximum boundaries
  // by one. Expecting a throw.
  bool caughtMaxPlusOne = false;
  try {
    multRangeCheck<int>(1, 2147483648);
  }
  catch (ValueRangeExceeded<int>) {
    caughtMaxPlusOne = true;
  }
  EXPECT_EQ(true, caughtMaxPlusOne);

  bool caughtMinMinusOne = false;
  try {
    multRangeCheck<int>(1, -2147483648);
  }
  catch (ValueRangeExceeded<int>) {
    caughtMinMinusOne = true;
  } 
  EXPECT_EQ(true, caughtMinMinusOne);

  // Negative range extends to one more
  // then positive range. Expecting a throw
  // if MIN_INT is made positive..
  bool caughtPositiveMin = false;
  try {
    multRangeCheck<int>(-2147483648, -1);
  }
  catch (ValueRangeExceeded<int>) {
    caughtPositiveMin = true;
  }
  EXPECT_EQ(true, caughtPositiveMin);
}

TEST(ArithmeticExceptions, FloatRangeCheck) {



}
