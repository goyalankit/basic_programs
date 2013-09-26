#include<stdio.h>

int findPeak(int *list, int pivot, int length){
  if(pivot + 1 < length && list[pivot] < list[pivot+1]){
    return findPeak(list, pivot / 2, length);
  }
  else if(pivot - 1 > 0 &&list[pivot] < list[pivot - 1]){
    return findPeak(list, pivot + pivot / 2, length);
  }
  else{
    return list[pivot];
  }
}

int main(void){

  int peak[10] = {2, 4, 5, 6, 7, 8, 9, 1, 3, 5 };
  int i = 0;

  printf( "peak is %d", findPeak(peak, 4, 10));
  return 0;
}
