#include "toymatrix.h"
#include "toyvector.h"
#include "arithmeticex.h"

#include <gtest/gtest.h>

#include <limits>
#include <cstdio>
using namespace std;


TEST(ToyVectorTest, DefaultContructed) {
  ToyVector<int> iVector;
  EXPECT_EQ(4, iVector.getNumRows());
  EXPECT_EQ(1, iVector.getNumColumns()); 
  EXPECT_EQ(false, iVector.isTransposed());

  EXPECT_EQ(0, iVector(0)); EXPECT_EQ(0, iVector(1)); EXPECT_EQ(0, iVector(2)); EXPECT_EQ(1, iVector(3));

  ToyVector<float> fVector;
  EXPECT_EQ(4, fVector.getNumRows());
  EXPECT_EQ(1, fVector.getNumColumns()); 
  EXPECT_EQ(false, iVector.isTransposed());

  EXPECT_EQ(0.0, fVector(0)); EXPECT_EQ(0.0, fVector(1)); EXPECT_EQ(0.0, fVector(2)); EXPECT_EQ(1.0, fVector(3));
}


TEST(ToyVectorTest, Initialization) {
  int iEntries[] = {13, 34, 54, 999, 78};
  int *iEntriesp = new int[5];
  memcpy(iEntriesp, &iEntries, 5*sizeof(int));
  ToyVector<int> iVector(5, iEntriesp);

  EXPECT_EQ(13, iVector(0)); EXPECT_EQ(34, iVector(1)); EXPECT_EQ(54, iVector(2)); EXPECT_EQ(999, iVector(3)); EXPECT_EQ(78, iVector(4));

  float fEntries[] = {13.0, 34.0, 54.0, 999.0, 78.0};
  float *fEntriesp = new float[5];
  memcpy(fEntriesp, &fEntries, 5*sizeof(float));
  ToyVector<float> fVector(5.0, fEntriesp);

  EXPECT_EQ(13.0, fVector(0)); EXPECT_EQ(34.0, fVector(1)); EXPECT_EQ(54.0, fVector(2)); EXPECT_EQ(999.0, fVector(3)); EXPECT_EQ(78.0, fVector(4));
} 

// Using ASSERT in this test, because subsequent tests
// make use of assignment and copy construction.
TEST(ToyVectorTest, CopyAndAssignment) {
  // Copy Construct a new object.
  int iEntries0[] = {13, 34, 54, 999, 87};
  int *iEntriesp0 = new int[5];
  memcpy(iEntriesp0, &iEntries0, 5*sizeof(int));
  ToyVector<int> iVector0(5, iEntriesp0);
  ToyVector<int> iVectorCopy(iVector0);

  ASSERT_EQ(5, iVectorCopy.getNumRows());
  ASSERT_EQ(1, iVectorCopy.getNumColumns());
  ASSERT_EQ(false, iVectorCopy.isTransposed());

  for(int row=0; row<iVectorCopy.getNumRows(); row++) {
      ASSERT_EQ(iVector0(row), iVectorCopy(row)) << "Copy Construction failed: entries in row: "<< row <<" differ";
  }

  // Assignment of vector with same dimensions.
  int iEntries1[] = {144, 425, 131, 999, 78};
  int *iEntriesp1 = new int[4*4];
  memcpy(iEntriesp1, &iEntries1, 5*sizeof(int));
  ToyVector<int> iVector1(5, iEntriesp1);
  iVector0 = iVector1;

  ASSERT_EQ(5, iVector0.getNumRows());
  ASSERT_EQ(1, iVector0.getNumColumns());
  ASSERT_EQ(false, iVector0.isTransposed());

  for(int row=0; row<iVectorCopy.getNumRows(); row++) {
      ASSERT_EQ(iVector1(row), iVector0(row)) << "Assignment of same dimensions failed: entries in row: " << row << "differ";
  }

  // Assignment of vector with different dimensions. 
  // This will delete the internal array and reallocate it.
  int iEntries2[] = {144, 425, 131, 999, 888, 78};
  int *iEntriesp2 = new int[6];
  memcpy(iEntriesp2, &iEntries2, 6*sizeof(int));
  ToyVector<int> iVector2(6, iEntriesp2);
  iVector0 = iVector2;

  ASSERT_EQ(6, iVector0.getNumRows());
  ASSERT_EQ(false, iVector0.isTransposed());

  for(int row=0; row<iVector0.getNumRows(); row++) {
      ASSERT_EQ(iVector2(row), iVector0(row)) << "Assignment of different dimensions failed: entries in row:" << row << "differ";
    }
}

TEST(ToyVectorTest, AddAndSubtract) {
  int iEntries0[] = {8383, 9243, 2194, 3498, 2432, 235};
  int *iEntriesp0 = new int[6];
  memcpy(iEntriesp0, &iEntries0, 6*sizeof(int));
  ToyVector<int> iVector0( 6, iEntriesp0); 
  ToyVector<int> iVector1(iVector0); 

  // Testing addition.
  ToyVector<int> resultIVector(iVector0+iVector1);

  for(int row=0; row<resultIVector.getNumRows()-1; row++) {
    int expectedResult = 2*iEntries0[row];
    EXPECT_EQ(expectedResult, resultIVector(row)) << "Addition operator produced an error for row: " << row;
  }
 
  // Testing subtraction.
  resultIVector = iVector0 - iVector1;
 
  for(int row=0; row<resultIVector.getNumRows()-1; row++) {
    EXPECT_EQ(0, resultIVector(row)) << "Subtraction operator produced an error for row: " << row;
  }

  // Testing addition and assignment operator.
  iVector0 += iVector1;

  for(int row=0; row<iVector0.getNumRows()-1; row++) {
    int expectedResult = 2*iEntries0[row];
    EXPECT_EQ(expectedResult, iVector0(row)) << "Addition and Assignment operator (add) produced and error for row: " << row; 
  }

  // Testing subtraction and assignment operator.
  iVector0 -= iVector1;

  for(int row=0; row<iVector0.getNumRows()-1; row++) {
    int expectedResult = iEntries0[row];
    EXPECT_EQ(expectedResult, iVector0(row)) << "Addition and Assignment operator (sub) produced and error for row: " << row;
  }
}

TEST(ToyVectorTest, MultiplyAndTranspose) {
  // First test with datatype int.
  // Test multiplication.
  int iEntries0[] = {838, 924, 342, 982, 23};
  int *iEntriesp0 = new int[5];
  memcpy(iEntriesp0, &iEntries0, 5*sizeof(int));
  ToyVector<int> iVector0(5, iEntriesp0);

  int iEntries1[] = {749, 987, 342, 233, 249};
  int *iEntriesp1 = new int[5];
  memcpy(iEntriesp1, &iEntries1, 5*sizeof(int));
  ToyVector<int> iVector1(5, iEntriesp1);

  // Transpose and multiply. Operands should have matching dimensions and must 
  // be transposed with respect to each other.
  iVector0.transpose();
  EXPECT_EQ(1, iVector0.getNumRows());
  EXPECT_EQ(5, iVector0.getNumColumns());
  EXPECT_EQ(true, iVector0.isTransposed()); 

  EXPECT_EQ(838, iVector0(0));  EXPECT_EQ(924, iVector0(1)); EXPECT_EQ(342, iVector0(2)); EXPECT_EQ(982, iVector0(3)); EXPECT_EQ(23, iVector0(4));

  int multResult = iVector0*iVector1;
  EXPECT_EQ(1656614, multResult); 

  // Dot product. Operands should have same dimensions and equal transposition.
  iVector0.transpose();
  int dotResult = iVector0*iVector1; 

  EXPECT_EQ(dotResult, multResult);

  // Cross product.
  ToyVector<int> iVector2 = iVector0.crossProduct(iVector1); 

  // Check if the resulting vector from the cross product 
  // operation is perpendicular to the generating vectors.
  EXPECT_EQ(0, iVector2*iVector0); 
  EXPECT_EQ(0, iVector2*iVector1); 
}

TEST(ToyVectorTest, ScalarMultiply)
{
  int *entries = new int[4];
  entries[0]=8; entries[1]=3; entries[2]=1; entries[3]=1;
  ToyVector<int> a(4, entries);

  // Do the scalar multiplication.
  a *= 2;

  // And check outcome.
  EXPECT_EQ(16, a(0)); EXPECT_EQ(6, a(1)); EXPECT_EQ(2, a(2)); EXPECT_EQ(1, a(3));
}

TEST(MatrixVectorTest, MatrixVectorMultiplication)
{
  // Create vector.
  int ivEntries0[] = {8383, 9243, 2194, 3498, 2432, 235};
  int *ivEntriesp0 = new int[6];
  memcpy(ivEntriesp0, &ivEntries0, 6*sizeof(int));
  ToyVector<int> iVector0( 6, ivEntriesp0);  

  // Create matrix.
  int imEntries0[] = {  33,  227,  203,   23, 2324,  32, 
                       345,  221,  344,  245,  393, 388,
                       234,  222,    3,  111,  918, 242,
                       223,  244,  299,  121,  325, 388,
                       234,  390,  164,   30, 2487, 786,
                       691,  203,  210,  953,  456,  77};
  int *imEntriesp0 = new int[6*6];
  memcpy(imEntriesp0, &imEntries0, 6*6*sizeof(int));
  ToyMatrix<int> iMatrix0( 6, 6, imEntriesp0);  

  // Now multiply.
  ToyVector<int> multResult = iMatrix0 * iVector0;

  EXPECT_EQ(8560124, multResult(0)); EXPECT_EQ(7593540, multResult(1)); 
  EXPECT_EQ(6697874, multResult(2)); EXPECT_EQ(6085545, multResult(3));
  EXPECT_EQ(12264242, multResult(4)); EXPECT_EQ(12590404, multResult(5));

  // Check if operator works for switched arguments.
  iVector0.transpose();
  multResult = iVector0 * iMatrix0;

  EXPECT_EQ(5490397, multResult(0)); EXPECT_EQ(6282409, multResult(1)); 
  EXPECT_EQ(6382023, multResult(2)); EXPECT_EQ(3421051, multResult(3));
  EXPECT_EQ(32421077, multResult(4)); EXPECT_EQ(7672359, multResult(5));

}
