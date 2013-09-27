#include <iostream>
#include <sys/time.h>


using namespace std;

struct timeval start, end;

int main() {

gettimeofday(&start, NULL);
  cout << "hello world!";

gettimeofday(&end, NULL);
double delta=0.0;
delta=  ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
cout << delta;
  return 0;
}
