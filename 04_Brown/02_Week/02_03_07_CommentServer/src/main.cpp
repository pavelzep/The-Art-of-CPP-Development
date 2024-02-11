#include "test_runner.h"
#include "tests.h"

using namespace Comment_Server;

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestServer<CommentServer>);
}
