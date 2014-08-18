#include <iostream>

// swap using pointers
void swap(int &a, int &b) {
  int temp(a);
  a = b;
  b = temp;
}

int main(void) {
  int a = 1;
  int b = 2;

  std::cout << "a = " << a << ", b = " << b << std::endl;
  swap(a, b);
  std::cout << "a = " << a << ", b = " << b << std::endl;

  return EXIT_SUCCESS;
}
