#include <iostream>
#include <string>
/**
 * a    b    c   d
 * ab   bc   cd
 * abc  bcd
 * abcd bd
 * abd
 * ac
 * acd
 * ad
 *
 * */

using namespace std;
void doPermute(string &in, string &out, int start) {
  for (int i = start; i < in.size(); ++i) {
    string out2 = out;
    out2 += in[i];
    std::cout << out2 << std::endl;
    doPermute(in, out2, i+1);
  }
}

int main(void) {
  string in = "abcd";
  string out = "";
  doPermute(in, out, 0);
  return EXIT_SUCCESS;
}
