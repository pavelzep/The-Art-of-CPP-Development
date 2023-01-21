#include <string>
using namespace std;

struct Specialization {
	string data;
	explicit Specialization(const string &new_data) {
		data = new_data;
	}
};
struct Course {
	string data;
	explicit Course(const string &new_data) {
		data = new_data;
	}
};

struct Week {
	string data;
	explicit Week(const string &new_data) {
		data = new_data;
	}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;
	LectureTitle(const Specialization &new_specialization,
			const Course &new_course, const Week &new_week) {
		specialization = new_specialization.data;
		course = new_course.data;
		week = new_week.data;
		;
	}
};

int main() {
	return 0;
}
