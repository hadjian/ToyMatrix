#ifndef TOY_ARITHMETIC_EXCEPTIONS
#define TOY_ARITHMETIC_EXCEPTIONS

#include "exception.h"

//----------------------------------------------------------------------
// Error-checking functions and exception classes for arithmetic 
// operations. 
//----------------------------------------------------------------------

template<class T>
class ValueRangeExceeded {
 public:
  ValueRangeExceeded(T op1 = T(), T op2 = T()) {
    Operator1 = op1; 
    Operator2 = op2; 
  }
  T Operator1;
  T Operator2; 
};

template<class T>
void multRangeCheck(T op1, T op2) {
  throw NotImplementedYet();
}

template<>
void multRangeCheck(float op1, float op2); 

template<>
void multRangeCheck(int op1, int op2);

#endif
