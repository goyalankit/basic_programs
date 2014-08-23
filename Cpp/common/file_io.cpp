#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>

using namespace std;

#define FILE_OPEN_ERROR(x) { \
  if (!x.is_open()) { \
    cerr << "Unable to open file "; \
    exit(EXIT_FAILURE); \
  } \
}

/*
 * Classes to read/write files:
 *
 * istream - stream class to read files. ios::in is assumed and combined.
 * ostream - stream class to write files. ios::out is assumed and combined.
 * fstream  - stream class to read and write files. ios::in | ios::out is assumed and is overridden.
 *
 *
 * All the above classes have constructor defined that calls open method.
 *
 * */


int main(void) {

  /*
   * Without the constructor and using ifstream.
   * */
  string inputFilename = "in.file";
  string line;

  ifstream inFile;
  inFile.open(inputFilename, ios::in);
  FILE_OPEN_ERROR(inFile);

  while (inFile >> line) {
    cout << line << endl;
  }
  inFile.close();

  /*
   * Calling the constructor with ifstream
   *
   * */

  ifstream inFile2 (inputFilename);
  FILE_OPEN_ERROR(inFile2);

  cout << "With constructor .." << "\n"; 
  while (inFile2 >> line) {
    cout << line << endl;
  }
  inFile2.close();

  fstream inFile3 (inputFilename);
  FILE_OPEN_ERROR(inFile3);

  std::cout << "Reading line using fstream" << std::endl;
  while(inFile3 >> line) {
    cout << line << endl;
  }
  inFile3.close();

  fstream inFile4 (inputFilename);
  FILE_OPEN_ERROR(inFile4);

  time_t ti = time(0);
  struct tm * t = localtime(&ti);

  std::cout << "writing to file" << std::endl;
  inFile4 << (t->tm_year + 1900) << "-" << (t->tm_mon + 1) << "-" << t->tm_mday << endl;
  inFile4.close();

  // to read file with a delimiter ','
  std::vector< vector<string> > result;
  fstream inFile5 ("comma.file");
  FILE_OPEN_ERROR(inFile5);
  std::cout << "---------------" << std::endl;
  while(getline(inFile5, line)) {
    stringstream ss(line);
    vector<string> line_vector(2);
    while(getline(ss, line, ',')){
      line_vector.push_back(line);
    }
    result.push_back(line_vector);
  } 

  return EXIT_SUCCESS;
}
