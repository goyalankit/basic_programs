#include<stdio.h>


void merge(int list[], int low, int mid, int high){
  int newI, k = mid + 1, newList[11],l;
  newI = low;
  l = low;

  while( newI <= mid && k <= high){
    if(list[newI] >= list[k]){
      newList[l++] = list[newI++];
    }
    else if(list[newI] < list[k]){
      newList[l++] = list[k++];
    }

    if(newI > mid){
      while(k<=high){
      newList[l++] = list[k++];
      }
    }
    else if(k > high){
      while(newI <= mid){
        newList[l++] = list[newI++];
      }
    }
  }
  for(l = low; l<=high; l++){
    list[l] = newList[l];
  }
}

int merge_sort(int list[], int low, int high){
  int mid;
  if (low < high) {
    mid = (low + high)/2;
    merge_sort(list, low, mid);
    merge_sort(list, mid + 1, high);
    merge(list, low, mid, high);
  }
  return 0;
}

int main(void){
  int input[11] = {2,4,5,6,1,5,9,3,1,4,6};
  int length = 11 ,i;
  
  for(i=0;i<11;i++){
    printf("%d ",input[i]);
  }

  printf("\n");
  merge_sort(input, 0, 10);

  for(i=0;i<11;i++){
    printf("%d ",input[i]);
  }

  return 0;
}

