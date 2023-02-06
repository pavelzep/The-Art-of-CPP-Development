#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <exception>

using namespace std;

class Matrix {
public:

    Matrix() {
        Reset(0, 0);
    }

    Matrix(int num_rows, int num_cols) {
        Reset(num_rows, num_cols);
    }

    void Reset(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("");
        } else {
            rows = num_rows;
            columns = num_cols;
            if (!(rows > 1 && columns > 1)) return;
            store.resize(num_rows);
            for (auto& item : store) {
                item.resize(0);
                item.resize(num_cols);
            }
        }
    }

    int At(int row, int column) const {
        if (row >= GetNumRows() || column >= GetNumColumns() || row < 0 || column < 0) {
            throw out_of_range("");
        }
        return store.at(row).at(column);
    }

    int& At(int row, int column) {
        if (row >= GetNumRows() || column >= GetNumColumns() || row < 0 || column < 0) {
            throw out_of_range("");
        }
        return store[row][column];
    }

    int GetNumRows() const {
        return rows;
    }

    int GetNumColumns() const {
        return columns;
    }

private:
    vector<vector<int>> store;
    int rows;
    int columns;
};

ostream& operator<<(ostream& stream, const Matrix& matrix) {

    int mRows = matrix.GetNumRows();
    int mCols = matrix.GetNumColumns();
    stream << mRows << " " << mCols << endl;

    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            stream << matrix.At(i, j);
            if (j != mCols - 1) stream << " ";
        }
        if (i != mRows - 1) stream << endl;
    }
    return stream;
}

istream& operator>>(istream& stream, Matrix& matrix) {
    int row, column;
    stream >> row >> column;

    matrix.Reset(row, column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            stream >> matrix.At(i, j);
        }
    }
    return stream;
}

Matrix  operator+(const Matrix& matrix1, const Matrix& matrix2) {

    int m1R = matrix1.GetNumRows();
    int m1C = matrix1.GetNumColumns();
    int m2R = matrix2.GetNumRows();
    int m2C = matrix2.GetNumColumns();

    bool flag = 1;
    flag = flag && (m1R == m2R) && (m1C == m2C);
    if (!flag) throw invalid_argument("");

    Matrix sum(m1R, m1C);

    for (int i = 0; i < m1R; i++) {
        for (int j = 0; j < m1C; j++) {
            sum.At(i, j) = matrix1.At(i, j) + matrix2.At(i, j);
        }
    }
    return sum;
}

bool  operator==(const Matrix& matrix1, const Matrix& matrix2) {

    int m1R = matrix1.GetNumRows();
    int m1C = matrix1.GetNumColumns();
    int m2R = matrix2.GetNumRows();
    int m2C = matrix2.GetNumColumns();

    bool flag = 1;
    flag = flag && (m1R == m2R) && (m1C == m2C);
    if (!flag) return flag;

    for (int i = 0; i < m1R; i++) {
        for (int j = 0; j < m1C; j++) {
            flag = flag && (matrix1.At(i, j) == matrix2.At(i, j));
            if (!flag) return flag;
        }
    }
    return flag;
}

int main() {
    Matrix one;
    Matrix two;

    // fstream fs("input.txt");
    // fs >> one >> two;

    one.Reset(1,1);
    int temp = one.At(0,0);
    
    //cin >> one >> two;
    //cout << one + two << endl;
    return 0;
}
