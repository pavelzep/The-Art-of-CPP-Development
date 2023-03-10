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
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>
#include <exception>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

//Date min_date = { 1900,01,01 };
Date min_date = { 1970,01,01 };
Date max_date = { 2100,01,01 };

Date date_from_string(const string& date_);

uint32_t position_from_date(const Date& date_);
uint32_t position_from_date2(const Date& date_);

void Add_money(const string& date_, const uint32_t value_, vector<uint32_t>& store_);

void Count_money(const string& from_, const string& to_, vector<uint32_t>& store_);

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

bool IsLeap(int year) {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

vector<int> sum_day_before_current_month = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

uint32_t day_of_year(const Date& date_) {
    uint32_t day_of_year = sum_day_before_current_month.at(date_.month - 1) + date_.day - 1;
    if (IsLeap(date_.year) && date_.month > 2) day_of_year += 1;
    return day_of_year;
}

uint32_t position_from_date2(const Date& date_) {
    tm min_tm{ 0,0,0,min_date.day,min_date.month - 1,min_date.year - 1900 };
    tm date_tm{ 0,0,0,date_.day,date_.month - 1,date_.year - 1900 };
    
    int day_diff = difftime(mktime(&date_tm), mktime(&min_tm)) / (24 * 60 * 60);
    return day_diff;
}

uint32_t position_from_date(const Date& date_) {

    uint32_t leap_year_correction = 0;
    for (int i = min_date.year; i < date_.year;++i) {
        if (IsLeap(i))  ++leap_year_correction;
    }

    uint32_t day_of_year_ = day_of_year(date_);
    uint32_t position = 365 * (date_.year - min_date.year) + leap_year_correction + day_of_year_;
    return position;
}

void Add_money(const string& date_, const uint32_t value_, vector<uint32_t>& store_) {
    uint32_t size = store_.size();
    uint32_t pos = position_from_date(date_from_string(date_));
    uint32_t pos2 = position_from_date2(date_from_string(date_));
    store_.at(pos + 1) += value_;//
}

void Count_money(const string& from_, const string& to_, vector<uint32_t>& store_) {
    uint32_t size = store_.size();

    uint32_t result;

    uint32_t pos_to = position_from_date(date_from_string(to_));
    uint32_t pos_from = position_from_date(date_from_string(from_));

    uint32_t value_to = store_.at(pos_to + 1);
    uint32_t value_from = store_.at(pos_from);

    result = value_to - value_from;

    cout << result << endl;
}

int main() {
    ostringstream out;
    try {

        vector<uint32_t> store(position_from_date(max_date) + 100);

        int store_size = store.size();

        //fstream cin("../input.txt");

        int e_count, q_count;
        cin >> e_count;

        while (e_count) {
            string date;
            uint32_t value;
            cin >> date >> value;
            out << date << ' ' << value << std::endl;
            Add_money(date, value, store);
            --e_count;
        }

        partial_sum(store.begin(), store.end(), store.begin());

        cin >> q_count;
        while (q_count) {

            string from, to;
            cin >> from >> to;
            out << from << ' ' << to << std::endl;
            Count_money(from, to, store);
            --q_count;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "err: " << out.str() << endl;
    }
    return 0;
}

