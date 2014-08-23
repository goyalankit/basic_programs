#include<iostream>
using namespace std;
int main()
{
  int p = 2;
  int *a = &p;
  char c = 'c';
  char *d = &c;
  std::cout << sizeof(d) << std::endl;
  return 0;
}
