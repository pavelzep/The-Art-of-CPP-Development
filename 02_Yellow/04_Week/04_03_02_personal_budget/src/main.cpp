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
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

enum class QueryType {
    ComputeIncome,
    Earn
};

tm start = { 0,0,0,1,0,100 };
tm fin = { 0,0,0,31,11,199 };

struct Query {
    QueryType type;
    tm from = {};
    tm to = {};
    double money;
};


istream& operator >> (istream& is, tm& from) {
    int temp;
    is >> temp;

    from.tm_year = temp - 1900;
    is.ignore(1);
    is >> temp;
    from.tm_mon = temp - 1;
    is.ignore(1);
    is >> temp;
    from.tm_mday = temp;
    return is;
}

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;

    if (operation_code == "ComputeIncome") {
        q.type = QueryType::ComputeIncome;
    } else if (operation_code == "Earn") {
        q.type = QueryType::Earn;
    }

    is >> q.from;

    is >> q.to;
    if (q.type == QueryType::Earn) {
        is >> q.money;
    }
    return is;
}

int position_from_date(tm& date) {

    return difftime(mktime(&date), mktime(&start)) / (60 * 60 * 24);

}

void Response(Query& q, vector<double>& in) {

    auto start_it = in.begin() + position_from_date(q.from);
    auto end_it = in.begin() + position_from_date(q.to);

    switch (q.type) {
    case QueryType::Earn: {

        // сколько дней между датами включая крайние даты
        int days = difftime(mktime(&q.to), mktime(&q.from)) / (60 * 60 * 24) + 1;
        // доход в день
        double earn_for_day = q.money / days;
        for (auto it = start_it; it != next(end_it); ++it) {
            *it += earn_for_day;
        }
        break;
    }
    case QueryType::ComputeIncome: {
        cout << setprecision(25) << accumulate(start_it, end_it + 1, 0.) << endl;

        break;
    }
    }
}

int main() {

    vector<double> income(difftime(mktime(&fin), mktime(&start)) / (60 * 60 * 24) + 1);

    int query_count;
    cin >> query_count;

    Query query;

    while (query_count) {
        --query_count;
        cin >> query;
        Response(query, income);
    }
    return 0;
}