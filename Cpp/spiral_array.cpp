#include <iostream>

/**
 * print spiral 2D array
 * input:
 * t => 1 2 3
 *      4 5 6
 * b => 7 8 9
 *      l   r
 * output: 1 2 3 6 9 8 7 4 5
 * dir:
 * 0 ->
 * 1 -> |
 * 2 -> <-
 * 3 -> |
 * */

void printSpiral(int a[][4], int m, int n) {
  // boundaties of the 2-D array.
  std::cout << "   Input Array" << std::endl;
  std::cout << "--------------------" << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << a[i][j] << " ";
    }
    std::cout << "" << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  int t = 0;
  int b = m -1;
  int l = 0;
  int r = n - 1;
  int dir = 0;

  while(t <= b && l <= r) {
    if (dir == 0) {
#ifdef DEBUG
      std::cout << "Going right " << l << " to " << r << std::endl;
#endif
      for (int i = l; i <= r; i++) {
        std::cout << a[t][i] << " ";
      }
      dir = 1;
      t++;
    } else if (dir == 1) {
#ifdef DEBUG
      std::cout << "Going down " << t << " to " << b << std::endl;
#endif
      for (int i = t; i <= b; i++) {
        std::cout << a[i][r] << " ";
      }
      dir = 2;
      r--;
    } else if (dir == 2) {
#ifdef DEBUG
      std::cout << "Going left " << r << " to " << l << std::endl;
#endif
      for (int i = r; i >= l; i--) {
        std::cout << a[b][i] << " ";
      }
      dir = 3;
      b--;
    } else if (dir == 3) {
#ifdef DEBUG
      std::cout << "Going up " << b << " to " << t << std::endl;
#endif
      for (int i = b; i >= t; i--) {
        std::cout << a[i][l] << " ";
      }
      dir = 0;
      l++;
    }
  }
}

int main(void) {
  int a[3][4] = {{1, 2, 3, 10}, {4, 5, 6, 11}, {7, 8, 9, 12}};
  printSpiral(a, 3, 4);
  return EXIT_SUCCESS;
}
