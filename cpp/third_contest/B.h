#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <sstream>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:

  T array[N][M];
  
  size_t RowsNumber() const {
    return N;
  }

  size_t ColumnsNumber() const {
    return M;
  }

  T& operator()(size_t index1, size_t index2) {
    return array[index1][index2];
  }

  
  const T& operator()(size_t index1, size_t index2) const {
    return array[index1][index2];
  }

  T& At(size_t index1, size_t index2) {
    if (index1 >= N || index2 >= M) {
      throw MatrixOutOfRange{};
    }
    return array[index1][index2];
  }

  const T& At(size_t index1, size_t index2) const {
    if (index1 >= N || index2 >= M) {
      throw MatrixOutOfRange{};
    }
    return array[index1][index2];
  }

 private:
  
};

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& matrix) {
  Matrix<T, M, N> answer;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      answer(j, i) = matrix(i, j);
    }
  }
  return answer;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
    Matrix<T, N, M> answer;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        answer(i, j) = first(i, j) + second(i, j);
      }
    }
  return answer;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
    Matrix<T, N, M> answer;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        answer(i, j) = first(i, j) - second(i, j);
      }
    }
  return answer;
}

template <class T, size_t N, size_t M, size_t P>
Matrix<T, N, P> operator*(const Matrix<T, N, M>& first, const Matrix<T, M, P>& second) {
  Matrix<T, N, P> answer;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < P; ++j) {
      answer(i, j) = 0;
      for (size_t k = 0; k < M; ++k) {
        answer(i, j) += first(i, k) * second(k, j);
      }
    }
  }
  return answer;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& operator+=(Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      first(i, j) += second(i, j);
    }
  }
  return first;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& operator-=(Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      first(i, j) -= second(i, j);
    }
  }
  return first;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& operator*=(Matrix<T, N, M>& first, const Matrix<T, M, M>& second) {
  Matrix<T, N, M> answer;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      answer(i, j) = 0;
      for (size_t k = 0; k < M; ++k) {
        answer(i, j) += first(i, k) * second(k, j);
      }
    }
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      first(i, j) = answer(i, j);
    }
  }
  return first;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M> operator*(const S value, const Matrix<T, N, M>& first) {
  Matrix<T, N, M> answer;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      answer(i, j) = first(i, j) * value;
    }
  }
  return answer;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& matrix, const S value) {
  return value * matrix;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M> operator/(const Matrix<T, N, M>& first, const S value) {
  Matrix<T, N, M> answer;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      answer(i, j) = first(i, j) / value;
    }
  }
  return answer;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M>& operator*=(Matrix<T, N, M>& matrix, const S value) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix(i, j) *= value;
    }
  }
  return matrix;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M>& operator/=(Matrix<T, N, M>& matrix, const S value) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix(i, j) /= value;
    }
  }
  return matrix;
}

template <class T, size_t N, size_t M>
bool operator==(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  for (size_t i = 0; i < N; ++i) {
     for (size_t j = 0; j < M; ++j) {
      if (first(i, j) != second(i, j)) {
          return false;
      }
    }
  }
  return true;
}

template <class T, size_t N, size_t M>
bool operator!=(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (first(i, j) != second(i, j)) {
        return true;
      }
    }
  }
  return false;
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      in >> matrix(i, j);
    }
  }
  return in;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      out << matrix(i, j);
      if (j < M - 1) {
        out << ' ';
      }
    }
    out << '\n';
  }
  return out;
}

#endif