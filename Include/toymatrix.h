//------------------------------------------------------------------------------
// - Transposed is of int type, so we can calculate with it. 
// ToyVector is a friend class of ToyMatrix,
// so we have direct access to its members and
// won't need to go through function calls for
// e.g. multiplication.
//
//
//------------------------------------------------------------------------------

#ifndef TOYMATRIX_H
#define TOYMATRIX_H

#include <arithmeticex.h>
#include <toyvector.h>

#include <cassert>
#include <iostream> 
using namespace std;

template<class T> class ToyVector;

template<class T>
class ToyMatrix {
  friend class ToyVector<T>;
 public:
  ToyMatrix(int rows = 4, int columns = 4, T* entries = 0x0);
  ToyMatrix(const ToyMatrix& other);
  ~ToyMatrix();

  ToyMatrix&   operator=(const ToyMatrix& rhs);
  T&           operator()(const int& row, const int& column) const; //TODO: check assembler output for inlined code

  ToyMatrix    operator*(const ToyMatrix&    rhs) throw(ValueRangeExceeded<T>);
  ToyVector<T> operator*(const ToyVector<T>& rhs) throw(ValueRangeExceeded<T>);
  ToyMatrix    operator+(const ToyMatrix&    rhs) throw(ValueRangeExceeded<T>);
  ToyMatrix    operator-(const ToyMatrix&    rhs) throw(ValueRangeExceeded<T>);

  ToyMatrix&   operator+=(const ToyMatrix& rhs)   throw(ValueRangeExceeded<T>);
  ToyMatrix&   operator-=(const ToyMatrix& rhs)   throw(ValueRangeExceeded<T>);
  ToyMatrix&   operator*=(const ToyMatrix& rhs)   throw(ValueRangeExceeded<T>);

  bool isTransposed();
  bool transpose();
  int getNumRows();
  int getNumColumns();
  void printValues() const;

 protected:
  int Rows, Columns;
  T* Entries;
  int Transposed;
};


//! entries: ownership goes to the object
template<class T>
ToyMatrix<T>::ToyMatrix(int rows /*= 4*/, int columns /*= 4*/, T* entries /*= 0x0*/) :
  Rows(rows),
  Columns(columns),
  Entries(entries),
  Transposed(0)
{
  if (!Entries) {
    Entries = new T[Rows*Columns];
    for (int i=0; i<(Rows*Columns); i++) {
      Entries[i] = T();
    }
  } else {
    Entries = entries;
  }
}

template<class T>
ToyMatrix<T>::ToyMatrix(const ToyMatrix& other) :
  Rows(0),
  Columns(0),
  Entries(0x0),
  Transposed(0)
{
  (*this) = other;
}


template<class T>
ToyMatrix<T>::~ToyMatrix()
{
  delete[] Entries;
}

template<class T>
inline ToyMatrix<T>& ToyMatrix<T>::operator=(const ToyMatrix& rhs)
{
  // Check for self-assignment
  if (this == &rhs) return (*this);
  if ((Rows != rhs.Rows) || (Columns != rhs.Columns)) {
    delete[] Entries;
    Transposed = rhs.Transposed;
    Columns = rhs.Columns;
    Rows = rhs.Rows;
    Entries = new T[Rows*Columns];
  }
  memcpy(Entries, rhs.Entries, Rows*Columns*sizeof(T));
  return (*this);
}

// INFO: Check assembler output whether this is actually inlined
template<class T>
inline T& ToyMatrix<T>::operator()(const int& row, const int& column) const
{
  assert(row < Rows && column < Columns);
  // To avoid if/else we put the index calculation of transposed
  // and non-transposed matrices into one calculation and multiply
  // by the Transpose flag, effectively clearing the unneeded part
  // by multiplication with zero.
  int notTransposed = (Transposed+1)%2;
  return Entries[notTransposed * (row*Columns+column) + Transposed * (column*Rows+row)];
}

template<class T>
inline ToyMatrix<T> ToyMatrix<T>::operator*(const ToyMatrix& rhs) throw (ValueRangeExceeded<T>)
{
  ToyMatrix result(Rows, rhs.Columns);
  for(int row=0; row < Rows; row++) {
    for(int column=0; column < rhs.Columns; column++) {
      for (int component=0; component < Columns; component++) {
#ifdef ARITHMETIC_EXCEPTIONS
        multRangeCheck((*this)(row, component), rhs(component, column));
#endif        
	result(row, column) += (*this)(row, component) * rhs(component, column);
      }
    }
  }
  return result;
}

template<class T>
inline ToyVector<T> ToyMatrix<T>::operator*(const ToyVector<T>& rhs) throw (ValueRangeExceeded<T>)
{
  assert(Columns==rhs.Rows);
  ToyVector<T> res(Rows);
  for (int i=0; i<Rows; i++)
  {
    for (int j=0; j<Columns; j++)
    {
      res(i) += (*this)(i,j) * rhs.Entries[j];
    }
  }
  return res;
}

template<class T>
inline ToyMatrix<T> ToyMatrix<T>::operator+(const ToyMatrix& rhs) throw (ValueRangeExceeded<T>) 
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  ToyMatrix result(Rows, Columns);
  for (int i=0; i < Rows; i++)
  {
    for (int j=0; j < Columns; j++) {
      result(i, j) = (*this)(i,j) + rhs(i,j);
    }
  }
  return result;
}

template<class T>
inline ToyMatrix<T> ToyMatrix<T>::operator-(const ToyMatrix& rhs) throw (ValueRangeExceeded<T>) 
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  ToyMatrix result(Rows, Columns);
  for (int i=0; i < Rows; i++)
  {
    for (int j=0; j < Columns; j++) {
      result(i, j) = (*this)(i,j) - rhs(i,j);
    }
  }
  return result;
}

template<class T>
inline ToyMatrix<T>& ToyMatrix<T>::operator+=(const ToyMatrix& rhs) throw (ValueRangeExceeded<T>) 
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  for (int i=0; i < Rows; i++) {
    for (int j=0; j < Columns; j++) {
      (*this)(i,j) += rhs(i,j);
    }
  }
  return (*this);
}

template<class T>
inline ToyMatrix<T>& ToyMatrix<T>::operator-=(const ToyMatrix& rhs) throw (ValueRangeExceeded<T>)
{
  assert(Rows==rhs.Rows && Columns==rhs.Columns);
  for (int i=0; i < Rows; i++) {
    for (int j=0; j < Columns; j++) {
      (*this)(i,j) -= rhs(i,j);
    }
  }
  return (*this);
}

template<class T>
inline ToyMatrix<T>& ToyMatrix<T>::operator*=(const ToyMatrix& rhs) throw (ValueRangeExceeded<T>) 
{
  assert(Columns == rhs.Rows);
  int newRows=Rows, newColumns=rhs.Columns;
  T *resultEntriesp = new T[newRows*newColumns]();
  for (int i=0; i<newRows; i++) {
    for (int j=0; j<newColumns; j++) {
      for (int component=0; component<Columns; component++) {
#ifdef ARITHMETIC_EXCEPTIONS
        multRangeCheck((*this)(i,component), rhs(component,j));
#endif
        resultEntriesp[i*newColumns+j]+= (*this)(i, component) * rhs(component, j);
      }
    }
  } 
  delete[] Entries; 
  Entries = resultEntriesp;
  Rows = newRows;
  Columns = newColumns;
  Transposed = 0;
  return (*this);
}

template<class T>
inline bool ToyMatrix<T>::isTransposed()
{
  return  (Transposed?true:false);
}

template<class T>
inline bool ToyMatrix<T>::transpose()
{
  Transposed = (Transposed+1)%2;
  int tmp = Rows;
  Rows = Columns;
  Columns = tmp;
  return (Transposed?true:false);
}

template<class T>
inline int ToyMatrix<T>::getNumRows()
{
  return Rows;
}

template<class T>
inline int ToyMatrix<T>::getNumColumns()
{
  return Columns;
}

template<class T>
void ToyMatrix<T>::printValues() const
{
  cout << "Pointer to Entries =" << Entries << "\n";
  for(int i=0; i < Rows; i++) {
    for(int j=0; j < Columns; j++) {
      cout << "("<< i <<","<< j << ")=" << (*this)(i,j) << ", ";
    }
    cout << "\n";
  }
  cout << "\n";
}


#endif // TOYMATRIX_H
