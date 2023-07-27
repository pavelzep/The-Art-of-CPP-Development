#include "test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

// Реализуйте шаблон Synchronized<T>.
// Метод GetAccess должен возвращать структуру, в которой есть поле T& value.

template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T());

  struct Access {
    T& ref_to_value;
  };

  Access GetAccess();
private:
  T value;
};


vector<int> Consume(Synchronized<deque<int>>& common_queue) {
  vector<int> got;

  for (;;) {
    deque<int> q;

    {
      // Мы специально заключили эти две строчки в операторные скобки, чтобы
      // уменьшить размер критической секции. Поток-потребитель захватывает
      // мьютекс, перемещает всё содержимое общей очереди в свою
      // локальную переменную и отпускает мьютекс. После этого он обрабатывает
      // объекты в очереди за пределами критической секции, позволяя
      // потоку-производителю параллельно помещать в очередь новые объекты.
      //
      // Размер критической секции существенно влияет на быстродействие
      // многопоточных программ.
      auto access = common_queue.GetAccess();
      q = move(access.ref_to_value);
    }

    for (int item : q) {
      if (item > 0) {
        got.push_back(item);
      } else {
        return got;
      }
    }
  }
}

