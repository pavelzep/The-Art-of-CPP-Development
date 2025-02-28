// Построение арифметического выражения
// Часть 1
// Реализуйте построение арифметического выражения согласно следующей схеме:
// изначально есть выражение, состоящее из некоторого целого числа x;
// на каждом шаге к текущему выражению применяется некоторая операция: 
// прибавление числа, вычитание числа, умножение на число или деление на число;
// перед применением операции выражение всегда должно быть заключено в скобки.
// Пример
// Изначально есть число 8, соответствующее выражение:
// 8
// К нему применяется операция умножения на 3, получается выражение
// (8) * 3
// Затем вычитается 6:
// ((8) * 3) - 6
// Наконец, происходит деление на 1; итоговое выражение:
// (((8) * 3) - 6) / 1
// Формат ввода
// В первой строке содержится исходное целое число x. Во второй строке содержится 
// целое неотрицательное число N— количество операций. В каждой из следующих N строк 
// содержится очередная операция:
// прибавление числа a: + a;
// либо вычитание числа b: - b;
// либо умножение на число c: * c;
// либо деление на число d: / d.
// Количество операций может быть нулевым — в этом случае необходимо вывести исходное число.
// Формат вывода
// Выведите единственную строку — построенное арифметическое выражение.
// Обратите внимание на расстановку пробелов вокруг символов:
// каждый символ бинарной операции (+, -, * или /) должен быть окружён ровно одним пробелом с каждой стороны: (8) * 3;
// символ унарного минуса (для отрицательных чисел) не нуждается в дополнительном пробеле: -5;
// скобки и числа не нуждаются в дополнительных пробелах.
// Подсказка
// Для преобразования числа к строке используйте функцию to_string из библиотеки <string>.
// Пример
// Ввод
// 8
// 3
// * 3
// - 6
// / 1
// Вывод
// (((8) * 3) - 6) / 1

// Часть 2. Без лишних скобок
// Модифицируйте решение предыдущей части так, чтобы предыдущее выражение
// обрамлялось скобками лишь при необходимости, то есть только в том случае,
// когда очередная операция имеет бо́льший приоритет, чем предыдущая.
// Пример
// Ввод
// 8
// 3
// * 3
// - 6
// / 1
// Вывод
// (8 * 3 - 6) / 1



#include <iostream>
#include <deque>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Operation {
    char type;
    int number;
};


bool isPriority(char a, char b) {
    return (a == '*' || a == '/') || (b == '+' || b == '-');
}

int main() {

    int init_value;
    int operations_count;

    vector<Operation> operations;
   // stringstream cin("8 3 *  3 -  6 /  1");
    //stringstream cin("6 3 * -1 / -1 + -3");
    cin >> init_value >> operations_count;

    Operation op;
    deque <string> expression;

    for (int i = 0; i < operations_count; ++i) {
        cin >> op.type;
        cin >> op.number;
        operations.push_back(op);
    }

    expression.push_back(to_string(init_value));
    auto it = operations.begin();
    while (it != operations.end()) {

        expression.push_back(" ");
        expression.push_back(string(1, it->type));
        expression.push_back(" ");
        expression.push_back(to_string(it->number));

        if (next(it) != operations.end()) {
            if (!isPriority(it->type, next(it)->type)) {
                expression.push_front("(");
                expression.push_back(")");
            }
        }
        it = next(it);
    }
    // expression.pop_back();
    // expression.pop_front();
    for (const auto& str : expression) {
        cout << str;
    }
    return 0;
}
