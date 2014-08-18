#include <iostream>
#include <stdio.h>

/**
 * return all possible words for a given telephone
 * number
 *
 * */

using namespace std;

#define NUMBER_LENGTH 3

// doesn't handle special case of 7 and 9. they don't
// have successive characters on them
char getCharKey(int telephoneKey, int place) {
  int base_a = (int)'A';
  int base_zero = '0';
  if (telephoneKey == 1 || telephoneKey == 0){
    return (char)(base_zero + telephoneKey);
  }
  return (char)(base_a + (telephoneKey - 2) * 3 + place-1);
}

void getTeleWord(int in[], string &out, int next){
  if (next >= NUMBER_LENGTH) {
    std::cout << out << std::endl;
    return;
  }

  for (int i = 1; i < 4; ++i) {
    string out2 = out;
    out2 += getCharKey(in[next], i);
    getTeleWord(in, out2, next+1);
    if (in[next] == 1 || in[next] == 0){
      return;
    }
  }
}

int main(void) {
  int in[NUMBER_LENGTH] = {1,2,3};
  string out = "";
  getTeleWord(in, out, 0);
  return EXIT_SUCCESS;
}
