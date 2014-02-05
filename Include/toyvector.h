#ifndef TOYVECTOR_H
#define TOYVECTOR_H

#include "toymatrix.h"

#include <cstring>
#include <cmath>
#include <cassert>

/*
// This is a generic vector that can have an arbitrary
// number of elements. Having a class that only allows
// a fixed number of elements would however allow
// convenient ctors, where element values can be
// specified at construction time.
*/

// Members Rows and Columns are interchanged when
// transposing the vector, such that these members
// can always be directly accessed w/o the need to
// check the transposed state.

template<class T>
class ToyVector {
  friend class ToyMatrix<float>;
  friend class ToyMatrix<int>;
public:
  // This enum is used for specifying whether
  // this is  a ROW or COLUMN vector
  enum TransposeType {COLUMN=0, ROW, MAX_ENUM};

  ToyVector(int rows = 4);
  ~ToyVector();
  ToyVector(const ToyVector& other);

  ToyVector& operator=(const ToyVector& rhs);
  T&         operator()(int index);
  T          operator*(const ToyVector& rhs);
  ToyVector  operator*(const ToyMatrix<T>& rhs);
  ToyVector  operator+(const ToyVector& rhs);
  ToyVector& operator+=(const ToyVector& rhs);
  ToyVector  operator-(const ToyVector& rhs);
  ToyVector& operator-=(const ToyVector& rhs);

  int        getNumEntries();
  ToyVector  crossProduct(const ToyVector& rhs);
  T          dotProduct(const ToyVector<T> &rhs);
  TransposeType transpose();
  ToyVector& normalize();
  ToyVector  normalized();

  void       printValues();
protected:
  int  Rows;
  int  Columns;
  TransposeType Transposed;
  int  NumEntries;
  T*   Entries;
};

template<class T>
ToyVector<T>::ToyVector(int rows /*=4*/) :
  Rows(rows),
  Columns(1),
  Transposed(COLUMN),
  NumEntries(rows)
{
  Entries = new T[rows];
  for (int i=0; i<rows; i++) {
    Entries[i] = T();
  }
}

template<class T>
ToyVector<T>::~ToyVector()
{
  delete[] Entries;
}

template<class T>
ToyVector<T>::ToyVector(const ToyVector& other) :
  Rows(0),
  Columns(0),
  Transposed(COLUMN),
  NumEntries(0),
  Entries(0x0)
{
  (*this) = other;
}

template<class T>
ToyVector<T>& ToyVector<T>::operator=(const ToyVector& rhs)
{
  if (this == &rhs) return *this;
  if (NumEntries != rhs.NumEntries) {
    delete Entries;
    NumEntries = rhs.NumEntries;
    Entries = new T[NumEntries];
  }
  Transposed=rhs.Transposed;
  Columns=rhs.Columns;
  Rows = rhs.Rows;
  memcpy(Entries, rhs.Entries, NumEntries*sizeof(T));
  return (*this);
}

template<class T>
T& ToyVector<T>::operator()(int index) {
  assert(index < NumEntries);
  return Entries[index];
}

template<class T>
T  ToyVector<T>::operator*(const ToyVector& rhs)
{
  assert(Columns==rhs.Rows);
  T res = T();
  for (int i=0; i<NumEntries; i++) {
    res += Entries[i]*rhs.Entries[i];
  }
  return res;
}

template<class T>
ToyVector<T> ToyVector<T>::operator*(const ToyMatrix<T>& rhs)
{
  assert(Columns== rhs.Rows);
  ToyVector<T> res(*this);
  for (int i=0; i<rhs.Columns; i++)
  {
    for (int j=0; j<Columns; j++)
    {
      res(i) += Entries[j]*rhs(j,i);
    }
  }
  return res;
}

template<class T>
ToyVector<T>  ToyVector<T>::operator+(const ToyVector& rhs)
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  ToyVector<T> res(NumEntries);
  return (res += rhs);
}

template<class T>
ToyVector<T>&  ToyVector<T>::operator+=(const ToyVector& rhs)
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  for (int i=0; i<NumEntries; i++)
  {
    Entries[i] += rhs.Entries[i];
  }
  return (*this);
}

template<class T>
ToyVector<T>  ToyVector<T>::operator-(const ToyVector& rhs)
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  ToyVector<T> res(NumEntries);
  return (res -= rhs);
}

template<class T>
ToyVector<T>&  ToyVector<T>::operator-=(const ToyVector& rhs)
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  for (int i=0; i<NumEntries; i++)
  {
    Entries[i] -= rhs.Entries[i];
  }
  return (*this);
}

template<class T>
int ToyVector<T>::getNumEntries()
{
  return NumEntries;
}

//TODO: Don't know if a cross product is extendable to more
//      dimensions as easy as I guessed it here.
template<class T>
ToyVector<T>  ToyVector<T>::crossProduct(const ToyVector& rhs)
{
  // WARNING: If you want to use this function, first check
  //          how a cross prod works on more than three
  //          dimensions and also on homogeneous coordinates.
  assert(0);
  assert(Rows=rhs.Rows && Columns==rhs.Columns);
  ToyVector<T> res(NumEntries);
  for (int i=0; i<NumEntries; i++)
  {
    int upperIndex=(i+1)%NumEntries;
    int lowerIndex=(i+2)%NumEntries;
    res(i) = Entries[upperIndex] * rhs.Entries[lowerIndex] - Entries[lowerIndex] * rhs.Entries[upperIndex];
  }
  return res;
}

template<class T>
T ToyVector<T>::dotProduct(const ToyVector<T>& rhs)
{
  assert(Rows==rhs.Rows);
  ToyVector<T> res = (*this).transposed();
  return res*rhs;
}

template<class T>
enum ToyVector<T>::TransposeType ToyVector<T>::transpose()
{
  int temp = Rows;
  Rows = Columns;
  Columns = temp;
  return Transposed?(ToyVector<T>::COLUMN):(ToyVector<T>::ROW);
}

// TODO: Make this more efficient
template<class T>
ToyVector<T>& ToyVector<T>::normalize()
{
  int sqrsum = 0;
  for (int i=0; i<NumEntries; i++)
  {
    sqrsum += Entries[i]*Entries[i];
  }
  printf("sqrsum:%i\n", sqrsum);
  float length = sqrt((float)sqrsum);
  for (int i=0; i<NumEntries; i++)
  {
    printf("e:%f\n", Entries[i]);
    Entries[i] /= length;
    printf("e:%f, length:%f\n", Entries[i], length);
  }
  return (*this);
}

template<class T>
ToyVector<T> ToyVector<T>::normalized()
{
  ToyVector<T> res(*this);
  return res.normalize();
}

template<class T>
void ToyVector<T>::printValues()
{
    printf("Pointer to Entries = %p\n", Entries);
    for(int i=0; i < NumEntries; i++) {
//      for(int j=0; j < Columns; j++) {
        printf("(%i)=%f ", i, (*this)(i));
  //    }
      printf(",");
    }
    printf("\n");
}


#endif // TOYVECTOR_H
