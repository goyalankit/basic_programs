#include<iostream>
#include "omp.h"

using namespace std;

int  main(){
  int nthreads;
  int tid;
#pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
      printf("hello %d\n", tid);

#pragma omp for
      for(int i=0; i<100; i++){
        cout <<  "haha" << tid << "  " << endl;
      }
  }

}
