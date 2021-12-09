#include <zero-containers.hpp>

#include <cassert>

void test_stack_t() {
  {
    stack_t<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.top() = 4;

    assert(stack.top() == 4);
    stack.pop();

    assert(stack.top() == 2);
    stack.pop();

    assert(stack.top() == 1);
    stack.pop();
  }

  {
    stack_t<int> stack;
    stack_t<int> const &stack_cref = stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    assert(stack_cref.size() == 3);

    stack.top() = 4;

    stack_t<int> const stack_copy = stack;

    assert(stack_copy.top() == 4);

    assert(stack_cref.top() == 4);
    stack.pop();

    assert(stack_cref.top() == 2);
    stack.pop();

    assert(stack_cref.top() == 1);
    stack.pop();
  }
}

void test_circular_buffer_t() {
  circular_buffer_t<int> buffer;
  circular_buffer_t<int> const &buffer_cref = buffer;

  buffer.push_back(0);
  buffer.push_back(1);
  buffer.push_back(2);

  assert(buffer[0] == 0);
  assert(buffer[1] == 1);
  assert(buffer[2] == 2);

  assert(buffer[0 + 3] == 0);
  assert(buffer[1 + 3] == 1);
  assert(buffer[2 + 3] == 2);

  assert(buffer.size() == 3);

  buffer.insert(1, 6);
  buffer[3] = 8;

  assert(buffer_cref.size() == 4);

  assert(buffer_cref[4 + 0] == 0);
  assert(buffer_cref[4 + 1] == 6);
  assert(buffer_cref[4 + 2] == 1);
  assert(buffer_cref[4 + 3] == 8);

  circular_buffer_t<int> const buffer_copy = buffer;

  assert(buffer_copy[4 + 0] == 0);
  assert(buffer_copy[4 + 1] == 6);
  assert(buffer_copy[4 + 2] == 1);
  assert(buffer_copy[4 + 3] == 8);
}

void test_sorted_vector_t() {
  sorted_vector_t<int> vec;
  sorted_vector_t<int> const &vec_cref = vec;

  vec.push_back(3).push_back(2).push_back(1).push_back(0);

  assert(vec_cref[0] == 0);
  assert(vec_cref[1] == 1);
  assert(vec_cref[2] == 2);
  assert(vec_cref[3] == 3);

  vec.push_back(2);

  assert(vec_cref[0] == 0);
  assert(vec_cref[1] == 1);
  assert(vec_cref[2] == 2);
  assert(vec_cref[3] == 2);
  assert(vec_cref[4] == 3);

  vec.erase(1);

  assert(vec_cref[0] == 0);
  assert(vec_cref[1] == 2);
  assert(vec_cref[2] == 2);
  assert(vec_cref[3] == 3);

  std::vector<int> res;
  for (auto const &v : vec_cref) {
    res.push_back(v);
  }

  assert(res[0] == 0);
  assert(res[1] == 2);
  assert(res[2] == 2);
  assert(res[3] == 3);
}

int main() {
  test_stack_t();
  test_circular_buffer_t();
  test_sorted_vector_t();

  return 0;
}
