#include <string>
using namespace std;

struct Specialization {
	string data;
	explicit Specialization(string new_data) {
		data = new_data;
	}
};
struct Course {
	string data;
	explicit Course(string new_data) {
		data = new_data;
	}
};

struct Week {
	string data;
	explicit Week(string new_data) {
		data = new_data;
	}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;
	LectureTitle(Specialization new_specialization, Course new_course, Week new_week){
		specialization = new_specialization.data;
		course = new_course.data;
		week =  new_week.data;
		;
	}
};

int main() {
	return 0;
}
