#ifndef TOYVECTOR_H
#define TOYVECTOR_H

#include <arithmeticex.h>
#include <toymatrix.h>

#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
using namespace std;

template<class T> class ToyMatrix;
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
  ToyVector(int rows = 4, T *entries = 0x0);
  ToyVector(const ToyVector& other);
  ~ToyVector();

  ToyVector& operator=(const ToyVector& rhs);
  ToyVector  operator+(const ToyVector& rhs);
  ToyVector  operator-(const ToyVector& rhs);
  T          operator*(const ToyVector<T>& rhs);
  ToyVector  operator*(const ToyMatrix<T>& rhs);
  ToyVector& operator+=(const ToyVector& rhs);
  ToyVector& operator-=(const ToyVector& rhs);
  T&         operator()(int index) const;

  int        getNumRows();
  int        getNumColumns(); 
  ToyVector  crossProduct(const ToyVector &rhs);
  T          dotProduct(const ToyVector<T> &rhs);
  bool       isTransposed();
  bool       transpose();
  ToyVector& normalize();
  ToyVector  normalized();

  void       printValues() const;
protected:
  int  Rows;
  int  Columns;
  int  Transposed;
  int  NumEntries;
  T*   Entries;
};

#include <toymatrix.h>

template<class T>
ToyVector<T>::ToyVector(int rows /*=4*/, T *entries /*= 0x0*/) :
  Rows(rows),
  Columns(1),
  Transposed(0),
  NumEntries(rows)
{
  if (!entries) {
    Entries = new T[rows];
    for (int i=0; i<rows-1; i++) {
      Entries[i] = T();
    }
    Entries[rows-1]=1;
  } else {
    Entries = entries;
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
  Transposed(0),
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
T& ToyVector<T>::operator()(int index) const
{
  assert(index < NumEntries);
  return Entries[index];
}

template<class T>
T  ToyVector<T>::operator*(const ToyVector<T>& rhs)
{
  assert(Columns==rhs.Rows);
  T res = T();
  for (int i=0; i<3; i++) {
#ifdef ARITHMETIC_EXCEPTIONS
        multRangeCheck((*this)(i), rhs(i));
#endif
    res += Entries[i]*rhs.Entries[i];
  }
  return res;
}

template<class T>
ToyVector<T> ToyVector<T>::operator*(const ToyMatrix<T>& rhs)
{
  assert(Columns == rhs.Rows);
  ToyVector<T> res(Columns);
  res.transpose();
  res(Columns-1)=0;
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
  ToyVector<T> res(*this);
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
  ToyVector<T> res(*this);
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
int ToyVector<T>::getNumRows()
{
  return Rows;
}

template<class T>
int ToyVector<T>::getNumColumns()
{
  return Columns;
}

//----------------------------------------------------------------------------- 
// A cross product on n-dimensional vectors is only defined for n-1 vectors. 
// Since this function deals with two operands, we can only do the cross
// product on three entries.
//----------------------------------------------------------------------------- 
template<class T>
ToyVector<T>  ToyVector<T>::crossProduct(const ToyVector& rhs)
{
  assert(0);
  assert(Rows=rhs.Rows && Columns==rhs.Columns);
  ToyVector<T> res(NumEntries);
  for (int i=0; i<3; i++)
  {
    int upperIndex=(i+1)%3;
    int lowerIndex=(i+2)%3;
    res(i) = Entries[upperIndex] * rhs.Entries[lowerIndex] - Entries[lowerIndex] * rhs.Entries[upperIndex];
  }
  return res;
}

template<class T>
T ToyVector<T>::dotProduct(const ToyVector<T>& rhs)
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  ToyVector<T> res(*this);
  res.transpose();
  return (T) (res*rhs);
}

template<class T>
bool ToyVector<T>::isTransposed()
{
  return (Transposed)?true:false;
}


template<class T>
bool ToyVector<T>::transpose()
{
  Transposed=(Transposed+1)%2;
  int temp = Rows;
  Rows = Columns;
  Columns = temp;
  return Transposed?true:false;
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
  float length = sqrt((float)sqrsum);
  for (int i=0; i<NumEntries; i++)
  {
    Entries[i] /= length;
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
void ToyVector<T>::printValues() const
{
    cout << "Pointer to Entries =" << Entries << "\n";
    for(int i=0; i < NumEntries; i++) {
      cout << "("<< i << ")="<< (*this)(i);
      cout << ",";
    }
    cout << "\n";
}


#endif // TOYVECTOR_H
