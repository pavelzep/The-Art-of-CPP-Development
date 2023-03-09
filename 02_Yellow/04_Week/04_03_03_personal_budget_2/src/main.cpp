// «Личный бюджет», starter plus edition
// Реализуйте систему ведения личного бюджета. Вам необходимо обрабатывать запросы следующих типов:
// date value: учесть, что в указанную дату была заработана сумма value.
// from to: вычислить прибыль за данный диапазон дат.
// Cначала идут только запросы с информацией о заработках, а потом — только запросы на вычисление прибыли.
// Примечания:
// Во всех диапазонах from to обе даты from и to включаются.
// Формат ввода:
// В первой строке вводится количество дней с информацией о заработках E, затем в описанном выше формате вводятся запросы, 
// по одному на строке. Затем вводится количество запросов Q на вычисление прибыли, а после в описанном выше формате вводятся
// запросы на вычисление прибыли, по одному на строке.
// Формат вывода:
// Для каждого запроса на вычисление прибыли в отдельной строке выведите целое число — прибыль за указанный диапазон дат.
// Ограничения:
// Количество запросов Q — натуральное число, не превышающее 100000.
// Все даты вводятся в формате YYYY-MM-DD. Даты корректны (с учётом високосных годов) и принадлежат интервалу с 1700 до 2099 гг.
// value — положительные целые числа, не превышающие 1000000.
// 4.9 секунды на обработку всех запросов.
// Подсказка:
// Используйте std::partial_sum, чтобы отвечать на каждый запрос, считая разность между двумя частичными суммами.
// Пример:
// Ввод:
// 3
// 2000-01-02 20
// 2000-01-06 10
// 2000-01-03 10
// 2
// 2000-01-01 2000-01-02
// 2000-01-02 2000-01-06
// Вывод:
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

struct Date {
    int year;
    int month;
    int day;
};

const string min_date_str = "1900-01-01";
const string max_date_str = "2099-12-31";

vector<int> days_from_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
vector<int> sum_of_days = { 0 };

Date date_from_string(const string& date_);

Date min_date = date_from_string(min_date_str);
Date max_date = date_from_string(max_date_str);

int position_from_date(const Date& date_);

void Processing_request_1(const string& date_, const int value_, vector<uint32_t>& store_);

void Processing_request_2(const string& from_, const string& to_, vector<uint32_t>& store_);

void init();

Date date_from_string(const string& date_) {

    stringstream ss(date_);
    Date date;
    ss >> date.year;
    ss.ignore(1);
    ss >> date.month;
    ss.ignore(1);
    ss >> date.day;
    return date;
}

int position_from_date(const Date& date_) {

    int leap_year_correction = 0;
    for (int i = min_date.year; i <= date_.year;++i) {
        if ((i % 4 == 0) && (i != 1700) && (i != 1800) && (i != 1900)) {
            ++leap_year_correction;
        }
    }

    int position = (date_.year - min_date.year) * 365 + sum_of_days[date_.month - 1] + date_.day + leap_year_correction - 1;
    return position;
}

void Processing_request_1(const string& date_, const int value_, vector<uint32_t>& store_) {
    int pos = position_from_date(date_from_string(date_));
    store_[pos] += value_;
}

void Processing_request_2(const string& from_, const string& to_, vector<uint32_t>& store_) {

    int pos_from = position_from_date(date_from_string(from_));
    int pos_to = position_from_date(date_from_string(to_));

    vector<int> sum_vect1;
    vector<int> sum_vect2;

    auto it_start = store_.begin() + pos_from;
    auto it_fin = store_.begin() + pos_to;

    partial_sum(store_.begin(), it_start + 1, back_inserter(sum_vect1));
    partial_sum(store_.begin(), it_fin + 1, back_inserter(sum_vect2));

    int result = sum_vect2.back() - sum_vect1.back() + store_[pos_from];
    cout << result << endl;
}

void init() {
    partial_sum(days_from_month.begin(), prev(days_from_month.end()), back_inserter(sum_of_days));
}

int main() {

    init();

    vector<uint32_t> store(position_from_date(date_from_string(max_date_str)) + 1);


    // Debug:

    // int size = store.size();
    // int debug_ = 0;

    // debug_ = position_from_date(date_from_string("1900-01-01"));
    // debug_ = position_from_date(date_from_string("2000-01-01"));
    // debug_ = position_from_date(date_from_string("2099-12-31"));
    
    // fstream cin("../input.txt");

    int e_count, q_count;

    cin >> e_count;

    while (e_count) {
        string date;
        int value;
        cin >> date >> value;
        Processing_request_1(date, value, store);
        --e_count;
    }

    cin >> q_count;
    while (q_count) {
        string from, to;
        cin >> from >> to;
        Processing_request_2(from, to, store);
        --q_count;
    }
    return 0;
}