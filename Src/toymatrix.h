#ifndef TOYMATRIX_H
#define TOYMATRIX_H

#include<assert.h>

template<class U> class ToyVector;

template<class T>
class ToyMatrix {
  // ToyVector is a friend class of ToyMatrix,
  // so we have direct access to its members and
  // won't need to go through function calls for
  // e.g. multiplication.
  friend class ToyVector<float>;
  friend class ToyVector<int>;
public:
  ToyMatrix(int rows = 4, int columns = 4) :
    Rows(rows),
    Columns(columns),
    Transposed(0)
  {
    Entries = new T[Rows*Columns];
    for (int i=0; i<(Rows*Columns); i++) {
      Entries[i] = T(); // value-initialized (zero for most primitives)
    }
  }

  ~ToyMatrix();

  ToyMatrix(const ToyMatrix& other) :
    Rows(0),
    Columns(0),
    Transposed(0),
    Entries(0x0)
  {
    printf("CCTor of ToyMatrix called\n");
    (*this) = other;
  }

  inline ToyMatrix& operator=(const ToyMatrix& rhs)
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
  inline T& operator()(const int& row, const int& column) const
  {
    // To avoid if/else we put the index calculation of transposed
    // and non-transposed matrices into one calculation and multiply
    // by the Transpose flag, effectively clearing the unneeded part
    // by multiplication with zero.
    int NotTransposed = (Transposed+1)%2;
    return Entries[NotTransposed * (row*Columns+column) + Transposed * (column*Rows+row)];
  }

  inline ToyMatrix operator*(ToyMatrix& rhs)
  {
    assert(Columns==rhs.Rows);
    ToyMatrix result(Rows, rhs.Columns);
    for(int row=0; row < Rows; row++) {
      for(int column=0; column < rhs.Columns; column++) {
        //scalar multiply
        for (int component=0; component < Columns; component++) {
          result(row, column) += (*this)(row, component) * rhs(component, column);
        }
      }
    }
    return result;
  }

  ToyVector<T> operator*(const ToyVector<T>& rhs);

  inline ToyMatrix operator+(const ToyMatrix& rhs)
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

  inline ToyMatrix operator-(const ToyMatrix& rhs)
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

  inline bool isTransposed()
  {
    return  (Transposed?true:false);
  }

  inline bool transpose()
  {
    Transposed = (Transposed+1)%2;
    int tmp = Rows;
    Rows = Columns;
    Columns = tmp;
    return (Transposed?true:false);
  }

  inline int getRows()
  {
    return Rows;
  }

  inline int getColumns()
  {
    return Columns;
  }

  void printValues()
  {
    printf("Pointer to Entries = %p\n", Entries);
    for(int i=0; i < Rows; i++) {
      for(int j=0; j < Columns; j++) {
        printf("(%i,%i)=%f ", i, j, (*this)(i,j));
      }
      printf("\n");
    }
    printf("\n");
  }

protected:
  int Rows, Columns;
  int Transposed;
  T* Entries;
};


template<class T>
ToyMatrix<T>::~ToyMatrix()
{
  delete[] Entries;
}

template<class T>
ToyVector<T> ToyMatrix<T>::operator*(const ToyVector<T>& rhs)
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


#endif // TOYMATRIX_H
