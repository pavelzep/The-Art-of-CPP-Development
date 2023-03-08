// «Личный бюджет», starter plus edition
// Реализуйте систему ведения личного бюджета. Вам необходимо обрабатывать запросы следующих типов:
// date value: учесть, что в указанную дату была заработана сумма value.
// from to: вычислить прибыль за данный диапазон дат.
// Cначала идут только запросы с информацией о заработках, а потом — только запросы на вычисление прибыли.
// Примечания:
// Во всех диапазонах from to обе даты from и to включаются.
// Формат ввода
// В первой строке вводится количество дней с информацией о заработках E, затем в описанном выше формате вводятся запросы, 
// по одному на строке. Затем вводится количество запросов Q на вычисление прибыли, а после в описанном выше формате вводятся
// запросы на вычисление прибыли, по одному на строке.
// Формат вывода
// Для каждого запроса на вычисление прибыли в отдельной строке выведите целое число — прибыль за указанный диапазон дат.
// Ограничения
// Количество запросов Q — натуральное число, не превышающее 100000.
// Все даты вводятся в формате YYYY-MM-DD. Даты корректны (с учётом високосных годов) и принадлежат интервалу с 1700 до 2099 гг.
// value — положительные целые числа, не превышающие 1000000.
// 4.9 секунды на обработку всех запросов.
// Подсказка
// Используйте std::partial_sum, чтобы отвечать на каждый запрос, считая разность между двумя частичными суммами.
// Пример
// Ввод
// 3
// 2000-01-02 20
// 2000-01-06 10
// 2000-01-03 10
// 2
// 2000-01-01 2000-01-02
// 2000-01-02 2000-01-06
// Вывод
// 20
// 40

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <numeric>
#include <fstream>




using namespace std;

tm string_to_date(const string& date_) {
    stringstream ss(date_);
    tm date = {};
    ss >> date.tm_year;
    date.tm_year -= 1900;
    ss.ignore(1);
    ss >> date.tm_mon;
    date.tm_mon -= 1;
    ss.ignore(1);
    ss >> date.tm_mday;
    date.tm_hour = 12;
    return date;
}

tm MIN_DATE = string_to_date("1900-01-01");
tm MAX_DATE = string_to_date("2099-12-31");

// tm MIN_DATE = { 0,0,0,1,0,0 };
// tm MAX_DATE = { 0,0,0,31,12,199 };

int position_from_date(tm& date) {
    return difftime(mktime(&date), mktime(&MIN_DATE)) / (60 * 60 * 24);
}

void Processing_request(const string& date_, const int value_, vector<uint32_t>& store_) {
    tm date = string_to_date(date_);
    int pos = position_from_date(date);
    store_[pos] += value_;
}

void Processing_request(const string& from_, const string& to_, vector<uint32_t>& store) {
    int result;
    tm tm_from = string_to_date(from_);
    int pos_from = position_from_date(tm_from);

    tm tm_to = string_to_date(to_);
    int pos_to = position_from_date(tm_to);

    vector<int> sum_vect1;
    vector<int> sum_vect2;

    auto it_start = store.begin() + pos_from;
    auto it_fin = store.begin() + pos_to;

    partial_sum(store.begin(), it_start + 1, back_inserter(sum_vect1));
    partial_sum(store.begin(), it_fin + 1, back_inserter(sum_vect2));

    result = sum_vect2.back() - sum_vect1.back() + store[pos_from];
    cout << result << endl;
}

int main() {

    vector<uint32_t> store(position_from_date(MAX_DATE));
    int size_v = store.size();

    tm tm_min = MIN_DATE;
    tm tm_max = MAX_DATE;

    time_t time_min = mktime(&tm_min);
    time_t time_max = mktime(&tm_max);

    // int sec = difftime(time_max, time_min) / (60 * 60 * 24);
    // cout << sec << endl;

    cout << size_v << endl;

    int e_count, q_count;

    fstream fs("input.txt");
    //cin >> e_count;

    while (e_count) {
        string date;
        int value;
        fs >> date >> value;
        Processing_request(date, value, store);
        --e_count;
    }

    fs >> q_count;
    while (q_count) {
        string from, to;
        fs >> from >> to;
        Processing_request(from, to, store);
        --q_count;
    }
    return 0;
}