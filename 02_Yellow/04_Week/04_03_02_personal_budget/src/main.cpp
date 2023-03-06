// «Личный бюджет», starter version
// Реализуйте систему ведения личного бюджета. Вам необходимо обрабатывать запросы следующих типов:
// ComputeIncome from to: вычислить чистую прибыль за данный диапазон дат.
// Earn from to value: учесть, что за указанный период (равномерно по дням) была заработана сумма value.
// Примечания:
// Во всех диапазонах from to обе даты from и to включаются.
// Формат ввода:
// В первой строке вводится количество запросов Q, затем в описанном выше формате вводятся сами запросы, по одному на строке.
// Формат вывода:
// Для каждого запроса ComputeIncome в отдельной строке выведите вещественное число — прибыль за указанный диапазон дат.
// Примечание:
// используйте std::cout.precision(25) в вашем коде для единообразия формата вывода вещественных чисел
// Ограничения:
// Количество запросов Q — натуральное число, не превышающее 50.
// Все даты вводятся в формате YYYY-MM-DD. Даты корректны (с учётом високосных годов) и принадлежат интервалу с 2000 до 2099 гг.
// value — положительные целые числа, не превышающие 1000000.
// 1 секунда на обработку всех запросов.
// Подсказка: Используйте std::accumulate для подсчёта сумм.
// Пример:
// Ввод:
// 5
// Earn 2000-01-02 2000-01-06 20
// ComputeIncome 2000-01-01 2001-01-01
// ComputeIncome 2000-01-01 2000-01-03
// Earn 2000-01-03 2000-01-03 10
// ComputeIncome 2000-01-01 2001-01-01
// Вывод:
// 20
// 8
// 30
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;


enum class QueryType {
    ComputeIncome,
    Earn
};

struct Date {
    int year;
    int month;
    int day;
};

struct Query {
    QueryType type;
    Date from;
    Date to;
};

istream& operator >> (istream& is, Date& d){

    is >> d.year;
    //пропуск символа.
    is >> d.month;
   //пропуск символа.
    is >> d.day;

}

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;

    if (operation_code == "ComputeIncome") {
        q.type = QueryType::ComputeIncome;

    } else if ((operation_code == "Earn") {
        q.type = QueryType::Earn;
    }

    

    return is;
}

int main() {

    int q;
        cin >> q;


    while (q) {
        --q;






    }
    return 0;
}