#include <vector>

struct one_byte { char x = 7; };
struct cheap_move {
  std::vector<one_byte> state{100000000}; // 100 mb of state, cheap to move
};
struct test_type {
  test_type(test_type const&)=default;
  test_type(test_type &&)=default;

  // can construct from a cheap_move via either copy or move:
  test_type(cheap_move const&y):x(y){}
  test_type(cheap_move &&y):x(std::move(y)){}

  cheap_move x;
};

test_type test_func() {
  cheap_move m;
  return m;
}

int main(int argc, char const *argv[])
{
	test_type k = test_func();
	return 0;
}
