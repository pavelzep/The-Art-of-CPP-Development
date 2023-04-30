Мы написали класс Substring, который можно использовать для создания подстрок без копирования. 
Какие методы надо добавить в него, чтобы работал код в функции main?

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
};

int main() {
  string three_words = "c++ red belt";
  Substring second_word{three_words, 4, 7};

  for (char& letter : second_word) {
    letter = toupper(letter);
  }
}
Выберите один вариант из списка

string::iterator start() { return s.begin() + first; } string::iterator finish() { return s.begin() + last; }
char start() { return s[first]; } char finish() { return s[last]; }
char begin() { return s[first]; } char end() { return s[last]; }
string::iterator begin() { return s.begin() + first; } string::iterator end() { return s.begin() + last; }
size_t begin() { return first; } size_t end() { return last; }