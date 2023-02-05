#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>



using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix {
public:

    Matrix() {
    }

    Matrix(int new_rows, int new_columns) {
        store.resize(new_rows);
        for (auto& item : store) {
            item.resize(new_columns);
        }
    }

    void Reset(int new_rows, int new_columns) {
        store.resize(new_rows);

        for (auto& item : store) {
            item.resize(0);

            item.resize(new_columns);
        }
    }

    int At(int row, int column) const {
        return store.at(column).at(row);
    }

    int& At(int row, int column) {
        return store[column][row];
    }

    int GetNumRows() const {
        return store.size();
    }

    int GetNumColumns() const {
        return store.at(0).size();
    }


private:
    vector<vector<int>> store;
};

ostream& operator<<(ostream& stream, const Matrix& matrix) {



    return stream;
}


istream& operator>>(istream& stream, Matrix& matrix) {
    int row, column;
    stream >> row >> column;

    matrix.Reset(row, column);
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < column; j++) {
           stream >> matrix.At(j,i) ;
        }
    }
    return stream;
}



Matrix  operator+(const Matrix& matrix1, const Matrix& matrix2) {

    return {};
}


int main() {
    Matrix one;
    Matrix two;

    fstream fs("input.txt");

    fs >> one >> two;
 //   cin >> one >> two;
 //   cout << one + two << endl;
    return 0;
}
