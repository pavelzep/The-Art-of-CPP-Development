#include <string>

using namespace std;


struct Substring {
  string& s;
  size_t first, last;

  char& operator[](size_t index) {
    return s[first + index];
  }

  const char& operator[](size_t index) const {
    return s[first + index];
  }

  size_t size() const {
    return last - first;
  }
  string::iterator begin() { return s.begin() + first; } 
  string::iterator end() { return s.begin() + last; }
};

int main() {
  string three_words = "c++ red belt";
  Substring second_word{three_words, 4, 7};

  for (char& letter : second_word) {
    letter = toupper(letter);
  }
}