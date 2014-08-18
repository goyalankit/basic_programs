#include <iostream>
#include <string>
#include <vector>
/**
 *
 * Generate all possible permutations of same length
 * */

using namespace std;

void permute(string& in, string& out, vector<bool>& used) {
  if (in.size() == out.size()) {
    std::cout << out << std::endl;
    return;
  }

  for (int i = 0; i < in.size(); i++) {
    if (used[i] == true) continue;
    string out2 = out;
    out2 += in[i];
    used[i] = true;
    permute(in, out2, used);
    used[i] = false;
  }
}

int main(void) {
  string in = "abcde";
  string out = "";
  vector<bool> used(in.size(), false);
  permute(in, out, used);
  return EXIT_SUCCESS;
}
