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

int position_from_date(const string& date_, vector<int>& sum_of_days_);

void Processing_request_1(const string& date_, const int value_, vector<uint32_t>& store_, vector<int>& sum_of_days_);
void Processing_request_2(const string& from_, const string& to_, vector<uint32_t>& store, vector<int>& sum_of_days_);

void init();

void init(vector<int>& days_from_month_, vector<int>& sum_of_days_) {

    partial_sum(days_from_month_.begin(), prev(days_from_month_.end()), back_inserter(sum_of_days_));
}

struct Date {
    int year;
    int month;
    int day;

};

int position_from_date(const string& date_, vector<int>& sum_of_days_) {
    stringstream ss(date_);
    Date date;
    ss >> date.year;
    ss.ignore(1);
    ss >> date.month;
    ss.ignore(1);
    ss >> date.day;

    int q = 0;
    for (int i = 1901; i < date.year;++i) {
        if ((i % 4 == 0)) {
            ++q;
        }
    }
    int result = (date.year - 1900) * 365 + sum_of_days_[date.month - 1] + date.day + q;
    return result;
}

void Processing_request_1(const string& date_, const int value_, vector<uint32_t>& store_, vector<int>& sum_of_days_) {

    int pos = position_from_date(date_, sum_of_days_);
    store_[pos] += value_;
}

void Processing_request_2(const string& from_, const string& to_, vector<uint32_t>& store, vector<int>& sum_of_days_) {
    int result;

    int pos_from = position_from_date(from_, sum_of_days_);
    int pos_to = position_from_date(to_, sum_of_days_);

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

    string min_date_str = "1900-01-01";
    string max_date_str = "2099-12-31";

    vector<int> days_from_month{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<int> sum_of_days = { 0 };

    init(days_from_month, sum_of_days);

    vector<uint32_t> store(position_from_date(max_date_str, sum_of_days));
    int size_v = store.size();

    int temp = position_from_date("1900-01-31", sum_of_days);

    int e_count, q_count;

    fstream cin("../input.txt");

    cin >> e_count;

    while (e_count) {
        string date;
        int value;
        cin >> date >> value;
        Processing_request_1(date, value, store, sum_of_days);
        --e_count;
    }

    cin >> q_count;
    while (q_count) {
        string from, to;
        cin >> from >> to;
        Processing_request_2(from, to, store, sum_of_days);
        --q_count;
    }
    return 0;
}