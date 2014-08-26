/*
Find next higher number with same digits.

Example 1 : if num = 25468, o/p = 25486

25468

21765
25761
26751
 _

Example 2 : if num = 21765, o/p = 25167
Example 3 : If num = 54321, o/p = 54321 (cause it's not possible to gen a higher num than tiz with given digits ).
*/

#include <iostream>
#include <vector>

using namespace std;
using byte = char;

// break int into digits and return in a byte array
inline vector<byte> *getDigits(int n) {
  vector<byte> *digits = new vector<byte>();
  int place = 0; // 0, 10's, 100's place
  int digit;
  while (n > 0) {
    digit = n % 10;
    digits -> push_back('0' + digit);
    n /= 10;
    ++place;
  }
  return digits;
}

ostream& operator<<(std::ostream &os, const vector<byte>& obj) {
  for (auto i = obj.begin(); i != obj.end(); ++i) {
    std::cout << *i << " ";
  }
  return os;
}

void swap(byte &i, byte &j) {
  byte temp = i;
  i = j;
  j = temp;
}

void reverse(vector<byte> &digits, int low, int end) {
  int temp;
  for (int i = low, j = end; i < j; i++, j--) {
    swap(digits[i], digits[j]);
  }
}

int numberFromDigits(vector<byte> &digits) {
  int number = 0;
  int base_number = '0';
  for (int i = 0; i < digits.size(); i++) {
    number = number * 10 + (int)(digits[i] - base_number);
  }
  return number;
}


int main(void) {
  int n = 45132;
  vector<byte> &digits = *(getDigits(n));
  // can be removed. run all the loops in opposite direction
  reverse(digits, 0, digits.size()-1);

  std::cout << "Input number: ";
  std::cout << n << std::endl;

  int swap_pos = -1;
  for (int i = digits.size() - 2; i >= 0; i--) {
    if (digits[i+1] > digits[i]) {
      swap_pos = i;
      break;
    }
  }
  // swap_pos = 3
  if (swap_pos == -1) return n;

  int swap_pos2 = -1;
  for (int i = digits.size()-1; i >=0; i--) {
    if (digits[i] > digits[swap_pos]) {
      swap_pos2 = i;
      break;
    }
  }

  swap(digits[swap_pos], digits[swap_pos2]);
  reverse(digits, swap_pos+1, digits.size()-1);

  std::cout << "Output number: ";
  std::cout << numberFromDigits(digits) << std::endl;

  return EXIT_SUCCESS;
}
