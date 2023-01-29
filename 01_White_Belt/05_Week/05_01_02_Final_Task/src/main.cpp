// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <string>
#include <map>
#include <iostream>
#include <exception>

using namespace std;

class Date {
public:
  Date() {
    year = 0;
    month = 0;
    day = 0;
  }

  Date(const int new_year, const int new_month, const int new_day) {
    if (new_month < 1 && new_month > 12) {
      throw exception();
    }
    if (new_day < 1 && new_day > 31) {
      throw exception();
    }
    day = new_day;
    month = new_month;
    year = new_year;
  }
  int GetYear() const {
    return year;
  };
  int GetMonth() const {
    return month;
  };
  int GetDay() const {
    return day;
  };

private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& left, const Date& right) {
  if (left.GetYear() < right.GetYear()) {
    return true;
  } else if (left.GetMonth() < right.GetMonth()) {
    return true;
  } else if (left.GetDay() <= right.GetDay()) {
    return true;
  } else
    return false;
};

bool operator==(const Date& left, const Date& right) {
  if ((left.GetYear() == right.GetYear()) && (left.GetMonth() == right.GetMonth()) && (left.GetDay() == right.GetDay())) {
    return true;
  } else
    return false;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event);
  bool DeleteEvent(const Date& date, const string& event);
  int DeleteDate(const Date& date);

  /* ??? */ Find(const Date& date) const;

  void Print() const;

private:
  map<Date, string> base;
};

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
  }

  return 0;
}