#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <istream>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
    return IteratorRange{ v.begin(), next(v.begin(), min(top, v.size())) };
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

// struct DataBase {
//     vector<Person> sort_by_age;
//     // map<Person, string> male_names;
//     // map<Person, string> female_names;
//     vector<size_t> sort_by_income;
// };

// DataBase ReadPeople(istream& input) {
//     int count;
//     input >> count;

//     DataBase result;
//     vector<Person> sort_by_age(count);
//     vector<size_t> sort_by_income(count);
//     std::iota(sort_by_income.begin(), sort_by_income.end(), 0);

//     for (Person& p : sort_by_age) {
//         char gender;
//         input >> p.name >> p.age >> p.income >> gender;
//         p.is_male = gender == 'M';
//     }

//     sort(begin(sort_by_age), end(sort_by_age), [](const Person& lhs, const Person& rhs) {
//         return lhs.age < rhs.age;
//         });


//     sort(begin(sort_by_income), end(sort_by_income), [& sort_by_age](size_t lhs, size_t rhs) {
//         return sort_by_age[lhs].age < sort_by_age[rhs].age;

//         });

//     result.sort_by_age = move(sort_by_age);
//     result.sort_by_income = move(sort_by_income);

//     return result;

// }


enum class request_type {
    AGE,
    WEALTHY,
    POPULAR_NAME_M,
    POPULAR_NAME_F,
};

struct StatisticResponse {
    request_type type;
    int count;
    int total_income;
    string name;
};

ostream& operator << (ostream& out, const StatisticResponse& resp) {



    return out;
};


StatisticResponse ServeRequest(string& command, string& request, vector<Person> sort_by_age) {
    StatisticResponse result;
    if (command == "AGE") {
        result.type = request_type::AGE;
        result.count = stoi(request);

    } else if (command == "WEALTHY") {
        result.type = request_type::WEALTHY;
        result.count = stoi(request);

    } else if (command == "POPULAR_NAME") {
        result.count = 0;
        if (request == "F") {
            result.type = request_type::POPULAR_NAME_F;
        } else {
            result.type = request_type::POPULAR_NAME_M;
        }

    }
    return result;
}


int main() {
    std::ifstream cin("../src/input.txt");
    std::ofstream out("../src/output.txt");
    // const DataBase db = ReadPeople(in);

    int count;
    cin >> count;
    vector<Person> sort_by_age(count);
    for (Person& p : sort_by_age) {
        char gender;
        cin >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }
    sort(begin(sort_by_age), end(sort_by_age), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
        });

    for (string command; cin >> command; ) {
        string request;
        cin >> request;
        StatisticResponse resp = ServeRequest(command, request, sort_by_age);
    }
    return 0;

    /*
        for (string command; cin >> command; ) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;

            auto adult_begin = lower_bound(
                begin(people), end(people), adult_age, [](const Person& lhs, int age) {
                    return lhs.age < age;
                }
            );

            cout << "There are " << std::distance(adult_begin, end(people))
                << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;

            auto head = Head(people, count);

            partial_sort(
                head.begin(), head.end(), end(people), [](const Person& lhs, const Person& rhs) {
                    return lhs.income > rhs.income;
                }
            );

            int total_income = accumulate(
                head.begin(), head.end(), 0, [](int cur, Person& p) {
                    return p.income += cur;
                }
            );
            cout << "Top-" << count << " people have total income " << total_income << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;

            IteratorRange range{
              begin(people),
              partition(begin(people), end(people), [gender](Person& p) {
                return p.is_male = (gender == 'M');
              })
            };
            if (range.begin() == range.end()) {
                cout << "No people of gender " << gender << '\n';
            } else {
                sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
                    return lhs.name < rhs.name;
                    });
                const string* most_popular_name = &range.begin()->name;
                int count = 1;
                for (auto i = range.begin(); i != range.end(); ) {
                    auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
                        return p.name == i->name;
                        });
                    auto cur_name_count = std::distance(i, same_name_end);
                    if (cur_name_count > count) {
                        count = cur_name_count;
                        most_popular_name = &i->name;
                    }
                    i = same_name_end;
                }
                cout << "Most popular name among people of gender " << gender << " is "
                    << *most_popular_name << '\n';
            }
        }
    }
    */
}
