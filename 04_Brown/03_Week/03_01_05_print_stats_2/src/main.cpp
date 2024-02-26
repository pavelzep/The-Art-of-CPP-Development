#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <sstream>
#include <optional>
#include <istream>
#include "test_runner.h"

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

enum class request_type {
    AGE,
    WEALTHY,
    POPULAR_NAME,
};

enum class response_type {
    AGE,
    WEALTHY,
    POPULAR_NAME,
    NO_PEOPLE
};

struct StatisticRequest {
    request_type type;
    int age;
    int wealthy_people_count;
    char gender;
};

struct StatisticResponse {
    response_type type;
    int age;
    int people_count;
    int total_income;
    string most_popular_name;
    char gender;
};

ostream& operator << (ostream& out, const StatisticResponse& resp) {
    switch (resp.type) {
        case response_type::AGE:
            out << "There are " << resp.people_count
                << " adult people for maturity age " << resp.age << '\n';
            break;
        case response_type::WEALTHY:
            out << "Top-" << resp.people_count << " people have total income " << resp.total_income << '\n';
            break;
        case response_type::POPULAR_NAME:
            cout << "Most popular name among people of gender " << resp.gender << " is "
                << resp.most_popular_name << '\n';
            break;
        case response_type::NO_PEOPLE:
            cout << "No people of gender " << resp.gender << '\n';
            break;
        default:
            break;
    }
    return out;
};

struct StatisticDataBase {
    optional<string> most_popular_male_name;
    optional<string> most_popular_female_name;
    vector<Person> sort_by_age;
    vector<int64_t> accumulate_welthy;
};

StatisticRequest PareseReqest(string& line) {

    StatisticRequest req;
    stringstream ss(line);
    string command;

    ss >> command;
    if (command == "AGE") {
        req.type = request_type::AGE;
        ss >> req.age;
    } else if (command == "WEALTHY") {
        req.type = request_type::WEALTHY;
        ss >> req.wealthy_people_count;
    } else if (command == "POPULAR_NAME") {
        req.type = request_type::POPULAR_NAME;
        ss >> req.gender;
    }

    return req;
}

StatisticResponse ServeRequest(const StatisticRequest& request, const StatisticDataBase& db) {
    StatisticResponse result;

    switch (request.type) {
        case request_type::AGE:
        {
            result.type = response_type::AGE;
            result.age = request.age;
            result.total_income = 0;
            result.most_popular_name = "";
            result.gender = 0;

            auto adult_begin = lower_bound(
                begin(db.sort_by_age), end(db.sort_by_age), result.age, [](const Person& lhs, int age) {
                    return lhs.age < age;
                }
            );
            result.people_count = std::distance(adult_begin, end(db.sort_by_age));
            break;
        }
        case request_type::WEALTHY:
        {
            result.type = response_type::WEALTHY;
            result.age = 0;
            result.most_popular_name = "";
            result.gender = 0;
            result.people_count = request.wealthy_people_count;
            result.total_income = db.accumulate_welthy[request.wealthy_people_count - 1];

            break;
        }
        case request_type::POPULAR_NAME:
        {
            result.age = 0;
            result.people_count = 0;
            result.total_income = 0;
            result.gender = request.gender;
            result.type = response_type::NO_PEOPLE;

            if (result.gender == 'M') {
                if (db.most_popular_male_name.has_value()) {
                    result.type = response_type::POPULAR_NAME;
                    result.most_popular_name = db.most_popular_male_name.value();
                }
            } else {
                if (db.most_popular_female_name.has_value()) {
                    result.type = response_type::POPULAR_NAME;
                    result.most_popular_name = db.most_popular_female_name.value();
                }
            }
            break;
        }
        default:
            break;
    }
    return result;
}
vector<Person> ReadPersons(istream& input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person& p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }

    return result;
}

template <typename Iter>
std::optional<string> getMostPopularName(IteratorRange<Iter> range) {
    if (range.begin() != range.end()) {
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
        return *most_popular_name;
    } else {
        return std::nullopt;
    }
}

StatisticDataBase createDataBase() {
    StatisticDataBase db;
    vector<Person> persons = ReadPersons(cin);

    {
        db.sort_by_age.resize(persons.size());
        partial_sort_copy(begin(persons), end(persons), db.sort_by_age.begin(), db.sort_by_age.end(), [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
            });
    }
    {
        vector<Person> sort_by_welthy(persons.size());
        std::partial_sort_copy(persons.begin(), persons.end(), sort_by_welthy.begin(), sort_by_welthy.end(), [](const Person& lhs, const Person& rhs) {
            return lhs.income > rhs.income;
            });

        db.accumulate_welthy.reserve(db.sort_by_age.size());
        for (auto& item : sort_by_welthy) {
            db.accumulate_welthy.push_back(move(item.income));
        }
        partial_sum(db.accumulate_welthy.begin(), db.accumulate_welthy.end(), db.accumulate_welthy.begin());
    }



    {
        auto it = partition(begin(persons), end(persons), [&persons](Person& p) {
            return p.is_male == true;
            });


        auto getMostPopularName_l = []<typename Iter>  (IteratorRange<Iter> range)-> std::optional<string> {
            if (range.begin() != range.end()) {
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
                return *most_popular_name;
            } else {
                return std::nullopt;
            }
        };

        {
            IteratorRange range{ begin(persons),it };
            db.most_popular_male_name = getMostPopularName_l(range);
        }

        {
            IteratorRange range{ it, end(persons) };
            db.most_popular_female_name = getMostPopularName_l(range);
        }
    }
    return db;
}

int main() {
    const StatisticDataBase db = createDataBase();

    for (string command; getline(cin, command);) {
        if (!command.empty()) {
            StatisticRequest request = PareseReqest(command);
            StatisticResponse resp = ServeRequest(request, db);
            cout << resp;
        }
    }
    return 0;
}
