#include "../Include/toymatrix.h"
#include "../Include/arithmeticex.h"

#include <gtest/gtest.h>

#include <limits>
#include <cstdio>
using namespace std;

TEST(ToyMatrixTest, DefaultContructed) {
  ToyMatrix<int> iMatrix;
  EXPECT_EQ(4, iMatrix.getRows());
  EXPECT_EQ(4, iMatrix.getColumns()); 
  EXPECT_EQ(false, iMatrix.isTransposed());

  EXPECT_EQ(0, iMatrix(0,0)); EXPECT_EQ(0, iMatrix(0,1)); EXPECT_EQ(0, iMatrix(0,2)); EXPECT_EQ(0, iMatrix(0,3));
  EXPECT_EQ(0, iMatrix(1,0)); EXPECT_EQ(0, iMatrix(1,1)); EXPECT_EQ(0, iMatrix(1,2)); EXPECT_EQ(0, iMatrix(1,3));
  EXPECT_EQ(0, iMatrix(2,0)); EXPECT_EQ(0, iMatrix(2,1)); EXPECT_EQ(0, iMatrix(2,2)); EXPECT_EQ(0, iMatrix(2,3));
  EXPECT_EQ(0, iMatrix(3,0)); EXPECT_EQ(0, iMatrix(3,1)); EXPECT_EQ(0, iMatrix(3,2)); EXPECT_EQ(0, iMatrix(3,3));

  ToyMatrix<float> fMatrix;
  EXPECT_EQ(4, fMatrix.getRows());
  EXPECT_EQ(4, fMatrix.getColumns()); 
  EXPECT_EQ(false, iMatrix.isTransposed());

  EXPECT_EQ(0, fMatrix(0,0)); EXPECT_EQ(0, fMatrix(0,1)); EXPECT_EQ(0, fMatrix(0,2)); EXPECT_EQ(0, fMatrix(0,3));
  EXPECT_EQ(0, fMatrix(1,0)); EXPECT_EQ(0, fMatrix(1,1)); EXPECT_EQ(0, fMatrix(1,2)); EXPECT_EQ(0, fMatrix(1,3));
  EXPECT_EQ(0, fMatrix(2,0)); EXPECT_EQ(0, fMatrix(2,1)); EXPECT_EQ(0, fMatrix(2,2)); EXPECT_EQ(0, fMatrix(2,3));
  EXPECT_EQ(0, fMatrix(3,0)); EXPECT_EQ(0, fMatrix(3,1)); EXPECT_EQ(0, fMatrix(3,2)); EXPECT_EQ(0, fMatrix(3,3));
}


TEST(ToyMatrixTest, Initialization) {
  int iEntries[] = {13, 34, 54, 999,
                    34, 35, 34, 233,
                    22, 22, 22,  11,
                     0,  0,  0,   1};
  int *iEntriesp = new int[4*4];
  memcpy(iEntriesp, &iEntries, 4*4*sizeof(int));
  ToyMatrix<int> iMatrix(4, 4, iEntriesp);

  EXPECT_EQ(13, iMatrix(0,0)); EXPECT_EQ(34, iMatrix(0,1)); EXPECT_EQ(54, iMatrix(0,2)); EXPECT_EQ(999, iMatrix(0,3));
  EXPECT_EQ(34, iMatrix(1,0)); EXPECT_EQ(35, iMatrix(1,1)); EXPECT_EQ(34, iMatrix(1,2)); EXPECT_EQ(233, iMatrix(1,3));
  EXPECT_EQ(22, iMatrix(2,0)); EXPECT_EQ(22, iMatrix(2,1)); EXPECT_EQ(22, iMatrix(2,2)); EXPECT_EQ( 11, iMatrix(2,3));
  EXPECT_EQ( 0, iMatrix(3,0)); EXPECT_EQ( 0, iMatrix(3,1)); EXPECT_EQ( 0, iMatrix(3,2)); EXPECT_EQ(  1, iMatrix(3,3));

  float fEntries[] = {13.0, 34.0, 54.0, 999.0,
                      34.0, 35.0, 34.0, 233.0,
                      22.0, 22.0, 22.0,  11.0,
                       0.0,  0.0,  0.0,   1.0};
  float *fEntriesp = new float[4*4];
  memcpy(fEntriesp, &fEntries, 4*4*sizeof(float));
  ToyMatrix<float> fMatrix(4.0, 4.0, fEntriesp);

  EXPECT_EQ(13.0, fMatrix(0,0)); EXPECT_EQ(34.0, fMatrix(0,1)); EXPECT_EQ(54.0, fMatrix(0,2)); EXPECT_EQ(999.0, fMatrix(0,3));
  EXPECT_EQ(34.0, fMatrix(1,0)); EXPECT_EQ(35.0, fMatrix(1,1)); EXPECT_EQ(34.0, fMatrix(1,2)); EXPECT_EQ(233.0, fMatrix(1,3));
  EXPECT_EQ(22.0, fMatrix(2,0)); EXPECT_EQ(22.0, fMatrix(2,1)); EXPECT_EQ(22.0, fMatrix(2,2)); EXPECT_EQ( 11.0, fMatrix(2,3));
  EXPECT_EQ( 0.0, fMatrix(3,0)); EXPECT_EQ( 0.0, fMatrix(3,1)); EXPECT_EQ( 0.0, fMatrix(3,2)); EXPECT_EQ(  1.0, fMatrix(3,3));
} 


// Using ASSERT in this test, because subsequent tests
// make use of assignment and copy construction.
TEST(ToyMatrixTest, CopyAndAssignment) {
  // Copy Construct a new object.
  int iEntries0[] = {13, 34, 54, 999,
		     34, 35, 34, 233,
	             22, 22, 22,  11,
	              0,  0,  0,   1};
  int *iEntriesp0 = new int[4*4];
  memcpy(iEntriesp0, &iEntries0, 4*4*sizeof(int));
  ToyMatrix<int> iMatrix0(4, 4, iEntriesp0);
  ToyMatrix<int> iMatrixCopy(iMatrix0);

  ASSERT_EQ(4, iMatrixCopy.getRows());
  ASSERT_EQ(4, iMatrixCopy.getColumns());
  ASSERT_EQ(false, iMatrixCopy.isTransposed());

  for(int row=0; row<iMatrixCopy.getRows(); row++) {
    for(int column=0; column<iMatrixCopy.getColumns(); column++) {
      ASSERT_EQ(iMatrix0(row, column), iMatrixCopy(row, column)) << "Copy Construction failed: entries in row:"
                                                                    << row<<"and column:"<< column<<" differ";
    }
  }

  // Assignment of matrix with same dimensions.
  int iEntries1[] = {144, 425, 131, 999,
                     788, 467, 607, 444,
                     678, 247, 123, 908,
                     123, 567, 343, 999};
  int *iEntriesp1 = new int[4*4];
  memcpy(iEntriesp1, &iEntries1, 4*4*sizeof(int));
  ToyMatrix<int> iMatrix1(4, 4, iEntriesp1);
  iMatrix0 = iMatrix1;

  ASSERT_EQ(4, iMatrix0.getRows());
  ASSERT_EQ(4, iMatrix0.getColumns());
  ASSERT_EQ(false, iMatrix0.isTransposed());

  for(int row=0; row<iMatrixCopy.getRows(); row++) {
    for(int column=0; column<iMatrixCopy.getColumns(); column++) {
      ASSERT_EQ(iMatrix1(row, column), iMatrix0(row, column)) << "Assignment of same dimensions failed: entries in row:"
                                                                    << row<<"and column:"<< column<<" differ";
    }
  }

  // Assignment of matrix with different dimensions. 
  // This will delete the internal array and reallocate it.
  int iEntries2[] = {144, 425, 131, 999, 888,
		    788, 467, 607, 444, 787,
		    123, 567, 343, 999, 734};
  int *iEntriesp2 = new int[3*5];
  memcpy(iEntriesp2, &iEntries2, 3*5*sizeof(int));
  ToyMatrix<int> iMatrix2(3, 5, iEntriesp2);
  iMatrix0 = iMatrix2;

  ASSERT_EQ(3, iMatrix0.getRows());
  ASSERT_EQ(5, iMatrix0.getColumns());
  ASSERT_EQ(false, iMatrix0.isTransposed());

  for(int row=0; row<iMatrix0.getRows(); row++) {
    for(int column=0; column<iMatrix0.getColumns(); column++) {
      ASSERT_EQ(iMatrix2(row, column), iMatrix0(row, column)) << "Assignment of different dimensions failed: entries in row:"
                                                                    << row<<"and column:"<< column<<" differ";
    }
  }
}

TEST(ToyMatrixTest, AddAndSubtract) {
  int iEntries0[] = {8383, 9243, 2194, 3498, 2432, 235,
                     3435, 9583, 5346, 9584, 3425, 345,
                     2355, 3426, 9340, 3495, 2352, 235,
                     9344, 9525, 3253, 2343, 3995, 434};
  int *iEntriesp0 = new int[4*6];
  memcpy(iEntriesp0, &iEntries0, 4*6*sizeof(int));
  ToyMatrix<int> iMatrix0(4, 6, iEntriesp0); 
  ToyMatrix<int> iMatrix1(iMatrix0); 

  // Testing addition.
  ToyMatrix<int> resultIMatrix(iMatrix0+iMatrix1);

  int rowWidth=resultIMatrix.getColumns();
  for(int row=0; row<resultIMatrix.getRows(); row++) {
    for(int column=0; column<resultIMatrix.getColumns(); column++) {
      int expectedResult = 2*iEntries0[row*rowWidth+column];
      EXPECT_EQ(expectedResult, resultIMatrix(row, column)) << "Addition operator produced an error for row:"
                                                            << row<< " and column:"<< column;
    }
  }
 
  // Testing subtraction.
  resultIMatrix = iMatrix0 - iMatrix1;
 
  rowWidth=resultIMatrix.getColumns();
  for(int row=0; row<resultIMatrix.getRows(); row++) {
    for(int column=0; column<resultIMatrix.getColumns(); column++) {
      EXPECT_EQ(0, resultIMatrix(row, column)) << "Subtraction operator produced and error for row:"
                                               << row<< "and column:"<< column;
    }
  }

  // Testing addition and assignment operator.
  iMatrix0 += iMatrix1;

  rowWidth=iMatrix0.getColumns();
  for(int row=0; row<iMatrix0.getRows(); row++) {
    for(int column=0; column<iMatrix0.getColumns(); column++) {
      int expectedResult = 2*iEntries0[row*rowWidth+column];
      EXPECT_EQ(expectedResult, iMatrix0(row, column)) << "Addition and Assignment operator produced and error for row:"
                                                       << row<< "and column:"<< column;
    }
  }

  // Testing subtraction and assignment operator.
  iMatrix0 -= iMatrix1;

  rowWidth=iMatrix0.getColumns();
  for(int row=0; row<iMatrix0.getRows(); row++) {
    for(int column=0; column<iMatrix0.getColumns(); column++) {
      int expectedResult = iEntries0[row*rowWidth+column];
      EXPECT_EQ(expectedResult, iMatrix0(row, column)) << "Addition and Assignment operator produced and error for row:"
                                                       << row<< "and column:"<< column;
    }
  }
}

TEST(ToyMatrixTest, MultiplyAndTranspose) {
  // First test with datatype int.
  // Test multiplication.
  int iEntries0[] = {8383, 9243,
                     3435, 9583,
                     2355, 3426};
  int *iEntriesp0 = new int[3*2];
  memcpy(iEntriesp0, &iEntries0, 3*2*sizeof(int));
  ToyMatrix<int> iMatrix0(3,2, iEntriesp0);

  int iEntries1[] = {7498, 9876,
                     2031, 3483};
  int *iEntriesp1 = new int[2*2];
  memcpy(iEntriesp1, &iEntries1, 2*2*sizeof(int));
  ToyMatrix<int> iMatrix1(2,2, iEntriesp1);

  ToyMatrix<int> iMatrix2(iMatrix0*iMatrix1);
  EXPECT_EQ(81628267, iMatrix2(0,0)); EXPECT_EQ(114983877, iMatrix2(0,1)); 
  EXPECT_EQ(45218703, iMatrix2(1,0)); EXPECT_EQ(67301649,  iMatrix2(1,1));
  EXPECT_EQ(24615996, iMatrix2(2,0)); EXPECT_EQ(35190738,  iMatrix2(2,1));

  // Now transpose.
  iMatrix2.transpose();
  EXPECT_EQ(2, iMatrix2.getRows());
  EXPECT_EQ(3, iMatrix2.getColumns());
  EXPECT_EQ(true, iMatrix2.isTransposed()); 

  EXPECT_EQ(81628267, iMatrix2(0,0));  EXPECT_EQ(45218703, iMatrix2(0,1)); EXPECT_EQ(24615996, iMatrix2(0,2));
  EXPECT_EQ(114983877, iMatrix2(1,0)); EXPECT_EQ(67301649, iMatrix2(1,1)); EXPECT_EQ(35190738,  iMatrix2(1,2));

  // Multiply transposed with untransposed.
  int iEntries2[] = { 23,  29, 
                      35,  48, 
                      34, 132};
  int *iEntries2p = new int[3*2];
  memcpy(iEntries2p, &iEntries2, 3*2*sizeof(int));
  ToyMatrix<int> iMatrix3(3, 2, iEntries2p);

  int iEntries3[] = {  156, 3498, 
                      3489, 3408,
                      2844, 9422};
  int *iEntries3p = new int[3*2];
  memcpy(iEntries3p, &iEntries3, 3*2*sizeof(int));
  ToyMatrix<int> iMatrix4(3, 2, iEntries3p);
  iMatrix4.transpose();

  iMatrix4 *= iMatrix3;
  EXPECT_EQ(false, iMatrix4.isTransposed()); 

  EXPECT_EQ(222399, iMatrix4(0,0)); EXPECT_EQ(547404, iMatrix4(0,1)); 
  EXPECT_EQ(520082, iMatrix4(1,0)); EXPECT_EQ(1508730, iMatrix4(1,1));

  // And now test with floats.
  float fEntries0[] = {8383.0, 9243.0,
                     3435.0, 9583.0,
                     2355.0, 3426.0};
  float *fEntriesp0 = new float[3*2];
  memcpy(fEntriesp0, &fEntries0, 3*2*sizeof(float));
  ToyMatrix<float> fMatrix0(3,2, fEntriesp0);

  float fEntries1[] = {7498.0, 9876.0,
                     2031.0, 3483.0};
  float *fEntriesp1 = new float[2*2];
  memcpy(fEntriesp1, &fEntries1, 2*2*sizeof(float));
  ToyMatrix<float> fMatrix1(2,2, fEntriesp1);

  ToyMatrix<float> fMatrix2(fMatrix0*fMatrix1);
  EXPECT_FLOAT_EQ(81628267.0, fMatrix2(0,0)); EXPECT_FLOAT_EQ(114983877.0, fMatrix2(0,1)); 
  EXPECT_FLOAT_EQ(45218703.0, fMatrix2(1,0)); EXPECT_FLOAT_EQ(67301649.0,  fMatrix2(1,1));
  EXPECT_FLOAT_EQ(24615996.0, fMatrix2(2,0)); EXPECT_FLOAT_EQ(35190738.0,  fMatrix2(2,1));

  // Now transpose.
  fMatrix2.transpose();
  EXPECT_FLOAT_EQ(2, fMatrix2.getRows());
  EXPECT_FLOAT_EQ(3, fMatrix2.getColumns());
  EXPECT_FLOAT_EQ(true, fMatrix2.isTransposed()); 

  EXPECT_FLOAT_EQ(81628267.0, fMatrix2(0,0));  EXPECT_FLOAT_EQ(45218703.0, fMatrix2(0,1)); EXPECT_FLOAT_EQ(24615996.0, fMatrix2(0,2));
  EXPECT_FLOAT_EQ(114983877.0, fMatrix2(1,0)); EXPECT_FLOAT_EQ(67301649.0, fMatrix2(1,1)); EXPECT_FLOAT_EQ(35190738.0,  fMatrix2(1,2));

  // Multiply transposed with untransposed.
  float fEntries2[] = { 23.0,  29.0, 
                      35.0,  48.0, 
                      34.0, 132.0};
  float *fEntries2p = new float[3*2];
  memcpy(fEntries2p, &fEntries2, 3*2*sizeof(float));
  ToyMatrix<float> fMatrix3(3, 2, fEntries2p);

  float fEntries3[] = {  156.0, 3498.0, 
                      3489.0, 3408.0,
                      2844.0, 9422.0};
  float *fEntries3p = new float[3*2];
  memcpy(fEntries3p, &fEntries3, 3*2*sizeof(float));
  ToyMatrix<float> fMatrix4(3, 2, fEntries3p);
  fMatrix4.transpose();

  fMatrix4 *= fMatrix3;
  EXPECT_FLOAT_EQ(false, fMatrix4.isTransposed()); 

  EXPECT_FLOAT_EQ(222399.0, fMatrix4(0,0)); EXPECT_FLOAT_EQ(547404.0, fMatrix4(0,1)); 
  EXPECT_FLOAT_EQ(520082.0, fMatrix4(1,0)); EXPECT_FLOAT_EQ(1508730.0, fMatrix4(1,1));
}

