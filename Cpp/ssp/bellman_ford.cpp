#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>

using namespace std;

int main(int argc, char **argv){

  if(argc < 3){
    cout << "Usage: ./a.out <filename(string)> <thread-count(int)>" << endl;
    exit(0);
  }

  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read();

  return 0;
}
