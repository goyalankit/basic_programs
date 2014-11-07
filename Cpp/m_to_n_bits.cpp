#include <iostream>
#include <string>
#include <bitset>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
using namespace std;

#define BIT_MASK (((unsigned) -1 >> (31 - (11))) & ~((1U << (6)) - 1))

int main(void) {
  int x = 12;
  size_t a = 7576160;
  unsigned set_number = a & BIT_MASK;
  std::bitset<32> x1(((unsigned) -1 >> 20));
  std::cout << x1;
  //cout << set_number;



  return EXIT_SUCCESS;
}

