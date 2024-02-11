#include "test_runner.h"
#include "tests.h"

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestServer<CommentServer>);
}
