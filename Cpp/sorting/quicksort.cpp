#include <iostream>
/*
 * pIndex     pivot
 * |           |
 * 7 1 2 6 5 3 4
 * start       end
 *
 *
 *
 *
 *
 *
 * */

void quickSort(int [], int, int);
void swap(int &, int &);
int partition(int [], int, int);

void printArray(int a[]) {
  std::cout << "----------------" << std::endl;
  for (int i = 0; i < 5; i++) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl << "----------------" << std::endl;
}

int main(void) {
  int a[5] = {5, 3, 1, 9, 12};
  std::cout << "Before sorting" << std::endl;
  printArray(a);
  quickSort(a, 0, 4);
  std::cout << "After sorting" << std::endl;
  printArray(a);
  return EXIT_SUCCESS;
}

/* Swaps to numbers passed by reference.
 *
 * Example:
 * a = 1; b = 2;
 *
 * swap(a,b); // a = 2, b = 1;
 *
 * */
void swap(int &a, int &b) {
  int temp(a);
  a = b;
  b = temp;
}

int partition(int *a, int start, int end) {
  int pivot = a[end];
  int pIndex = start;

  for(int i = start; i < end; ++i) {
    if(a[i] < pivot) {
      swap(a[i], a[pIndex]);
      pIndex += 1;
    }
  }
  swap(a[pIndex], a[end]);
  return pIndex;
}

void quickSort(int *a, int start, int end) {
  // check that indices are valid
  if (end <= start) { return; }
  int pIndex = partition(a, start, end);
  quickSort(a, start, pIndex-1);
  quickSort(a, pIndex+1, end);
}
