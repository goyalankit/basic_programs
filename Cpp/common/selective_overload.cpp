#include <iostream>
#include <vector>

using namespace std;

// helper method to determine if << operator exists for type T
// return false if unused evalues to ostream
template<typename T, typename unused = decltype(cout << T())>
std::false_type has_ostream_helper(const T&);

template<typename T>
std::true_type has_ostream_helper(const T&);

// enable this template only if << operator doesn't exists already
template <typename T, typename enable_if<decltype(has_ostream_helper<T>)::value, T>::type* = nullptr>
ostream& operator<<(std::ostream &os, const T& obj) {
  for (auto i = obj.begin(); i != obj.end(); ++i) {
    std::cout << *i << std::endl;
  }
  return os;
}


int main(void) {
  int n = 45132;
  vector<int> digits = {1, 2, 3, 4, 5};
  std::cout << digits << std::endl;

  return EXIT_SUCCESS;
}

