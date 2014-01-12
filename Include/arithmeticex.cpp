#include "arithmeticex.h"
#include "exception.h"

#include <limits>
#include <stdio.h>
using namespace std;

// TODO: Throw exception when we're in subnormal
// or close to overflow?
template<>
void multRangeCheck(float op1, float op2) throw (ValueRangeExceeded<float>) {
  float min = numeric_limits<float>::min(); 
  float max = numeric_limits<float>::max(); 

  if (op1 == 0 || op2 == 0 ) return;
  if (op1 < 0) {
    if ( (op2 > 0) && !(min/op2 <= op1) ) throw ValueRangeExceeded<float>(op1,op2); 
    if ( (op2 < 0) && !(max/op2 <= op1) ) throw ValueRangeExceeded<float>(op1,op2);  
  } else {
    if ( (op2 > 0) && !(max/op2 >= op1) ) throw ValueRangeExceeded<float>(op1,op2);
    if ( (op2 < 0) && !(min/op1 <= op2) ) throw ValueRangeExceeded<float>(op1,op2);
  }
} 

//--------------------------------------------------------------
// Function multRangeCheck()<int>
//--------------------------------------------------------------
//
// Uses precomputation to test whether multiplication will 
// leave the range supported by the int-type.
//
// The inequality we're checking is:
// 
// MIN_VALUE <= op1 * op2 <= MAX_VALUE
//
// In terms of supported C++-operations, this becomes:
//
// MIN_VALUE <= op1 * op2 && MAX_VALUE >= op1 * op2 (1)
//
// Since int-types wrap around, this expression always
// holds true, so we divide by op2, which will do anything to
// the MAX/MIN values, but throwing it out of the range (with
// one exception explained below):
//
// MIN_VALUE/op2 <= op1 && MAX_VALUE/op2 >= op1,    (2)
//
// but dividing by a variable in an inequality requires a case-
// by-case analysis for [-inf, -1] and [1,inf]. The intervall
// ]-1,1[ can be ignored, because an op2 in that range would
// only bring any op1 towards zero (no need to test) but 
// wouldn't work in (2) (and throw an exception for op2=0):
//
// MIN_VALUE/op2 >= op1 && MAX_VALUE/op2 <= op1,
// for op2 in [-inf,-1] and
//
// MIN_VALUE/op2 <= op1 && MAX_VALUE/op2 >= op1,
// for op2 in [1,inf]
//
// There is one case though, which will also throw the result
// of the division operation out of the range, which is min/-1.
// This is due to the negative range extending to one more in
// magnitude. 
//--------------------------------------------------------------
template<>
void multRangeCheck<int>(int op1, int op2) throw(ValueRangeExceeded<int>) {
  int min = numeric_limits<int>::min();
  int max = numeric_limits<int>::max();
  
  if ( op2<-1 ? !(min/op2 >= op1 && max/op2 <= op1) :  
         op2>= 1 ? !(min/op2 <= op1 && max/op2 >= op1) : 
           (op2 == -1 && op1 == min) ) {
    throw ValueRangeExceeded<int>(op1, op2);
  }
} 

