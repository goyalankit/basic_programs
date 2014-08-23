#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;
/*
 * Method: abbreviateWord(string word, int offset)
 *
 * Example: internationalization, 1: i18n
 *          auto, 1: a2o
 *          automatic, 2: au5ic
 * */

string abbreviateWord(string word, int offset) {
  int length = word.length();
  int numeric_part;
  if (offset > length) {
    return NULL;
  }
  string prefix = word.substr(0, offset);
  string suffix = word.substr(length-offset, length-offset);
  numeric_part = length - (2 * offset);
  string result;
  if (numeric_part < 1)
    result = prefix + suffix;
  else
    result = prefix + to_string(numeric_part) + suffix;
  return result;
}

/** Returns unique mapping of abbreviations to words for a given list of words.
 * Input:
 * words: vector of words of string datatype.
 *
 * Return:
 * map with keys as abbreviations and values as the corressponding words.
 *
 * Example:
 * Input: ["abcdef", "abpqef", "internationalization", "something"]
 * Output:
 *
 * acdef ->  ac1ef
 * doordonotthereisnotry ->  d19y
 * cool ->  c2l
 * aqref ->  aq1ef
 * internationalization ->  i18n
 *
 * */
unordered_map<string, string>& uniqueAbbreviation(const vector<string>& words) {
  // maintain a hash map with abbv -> word mapping.
  unordered_map<string, string> *abbvWord = new unordered_map<string, string>();
  // maintain a queue for processing words.
  queue<string> wordQueue;
  int offset = 1; // initial offset
  // loop until all done
  for (auto &it : words) {
    wordQueue.push(it);
  }
  string word, abbv;
  int count = wordQueue.size();
  while(!wordQueue.empty()) {
    word = wordQueue.front();
    wordQueue.pop();

    abbv = abbreviateWord(word, offset);
    if ((*abbvWord)[abbv] == "") {
      (*abbvWord)[abbv] = word;
    } else {
      wordQueue.push(((*abbvWord)[abbv]));
      abbvWord->erase(abbv);
      wordQueue.push(word);
    }
    count--;
    if (count == 0) {
      count = wordQueue.size();
      offset++;
    }
  }
  return *abbvWord;
}

int main(void) {
  std::cout << "Internationaalization, 1: " << abbreviateWord("internationalization", 1) << endl;
  std::cout << "Internationalization, 2: " <<  abbreviateWord("internationalization", 2) << endl;
  std::cout << "abcdef, 3: " <<  abbreviateWord("abcdef", 3) << endl;
  vector<string> words = {"internationalization", "cool"};
  words.push_back("doordonotthereisnotry");
  words.push_back("acdef");
  words.push_back("aqref");

  unordered_map<string, string> &abbvWords = uniqueAbbreviation(words);

  for(auto &it : abbvWords) {
    std::cout << it.second << " ->  " << it.first << std::endl;
  }

  return EXIT_SUCCESS;
}
