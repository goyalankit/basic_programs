/**
 *
 * This method splits a given string.
 *
 * 
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(const string&, char);


int main(void) {
  int a;
  void *onHeap = malloc(128);
  std::cout << "Stack address is " << &a << std::endl;
  std::cout << "Heap address is " << onHeap << std::endl;
  string sample = "This, is, a, sample, string";
  std::cout << "Reference of sample string " << &sample << std::endl;
  std::cout << "sample is on stack" << std::endl;
  // copy constructor does a shallow copy
  vector<string> output = split(sample, ',');
  vector<string> *output2;
  std::cout << "Reference outside split for vector " << &output << std::endl;
  std::cout << "Reference for values in output " << &output[0] << std::endl;
  std::cout << "Reference for output2 " << &output2 << std::endl;
  return 0;
}

vector<string> split(const string &input, char delim) {
  std::cout << "Reference of input " << &input << std::endl;
  vector<string> elem;
  elem.push_back("hello");
  std::cout << "Reference inside split for vector " << &elem << std::endl;
  return elem;
}
