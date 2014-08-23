#include <iostream>
#include <limits>

/*
 * int input[5] = {1,2,3,4,5};
 * input is of array type. You can do something like:
 * sizeof(input)/sizeof(input[0]) to get the size.
 *
 * However, if you pass this to a function, it degenerates into
 * pointer type and sizeof(input)/sizeof(input[0]) is no longer
 * valid.
 *
 * You should consider using vector or array class in cpp.
 *
 * */


int largest(int[], int);

int main(void) {
  int input[5] = {1,2,10,4,5};
  std::cout << largest(input, 5) << std::endl;
  return EXIT_SUCCESS;
}


int largest(int input[], int length) {
  int max = std::numeric_limits<int>::min();
  std::cout << "size of input " << sizeof(input) << std::endl;
  for (int i = 0; i < length; ++i) {
    if (max < input[i]) {
      max = input[i];
    }
  }
  return max;
}
