#include <Include/arithmeticex.h>

#include <gtest/gtest.h>

#include <cstdio>
#include <limits>
using namespace std;

TEST(ArithmeticExceptions, IntRangeCheck) {
  // Store the machine-dependent boundary
  // values locally.
  int max = numeric_limits<int>::max();
  int min = numeric_limits<int>::min();

  // 0, -1 and 1 as the intervall boundaries,
  // internal to the multRangeCheck function.
  multRangeCheck<int>(0, 0);
  multRangeCheck<int>(-1000, -1);
  multRangeCheck<int>(-1000, 1);
  multRangeCheck<int>(1, 2147483647);
  multRangeCheck<int>(-1, -2147483647);
  multRangeCheck<int>(1, -2147483648);
  multRangeCheck<int>(-1, 2147483647);

  // Overstep minimum and maximum boundaries
  // by one. Expecting a throw.
  bool caughtMaxPlusOne = false;
  try {
    int double_overflows = max/2+1;
    multRangeCheck<int>(2, double_overflows);
  }
  catch (ValueRangeExceeded<int>) {
    caughtMaxPlusOne = true;
  }
  EXPECT_EQ(true, caughtMaxPlusOne);

  bool caughtMinMinusOne = false;
  try {
    int double_underflows = min/2-1; 
    multRangeCheck<int>(2, double_underflows);
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
