#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>

using namespace std;
/*
bool com(vector <pair<int, double> > fir, vector <pair<int, double> > sec){
return (fir.second > sec.second)
}

*/

struct sort_pred {
    bool operator()(const std::pair<int,double> &left, const std::pair<int,double> &right) {
        return left.second > right.second;
    }
};


int main(int argc, char** argv ){

  if(argc < 3){
    cout << "Usage: ./a.out <filename(string)> <vertex-count(int)>" << endl;
    exit(0);
  }

  vector< pair<int, double> > page_rank;
  char *filename = argv[1];
  int node;
  double weight;

  cout << "reading file and trying to find number of vertices" << endl;
  ifstream read(filename);
  while(read >> node >> weight){
    page_rank.push_back( std::make_pair( node, weight ));
  }

  std::sort(page_rank.begin(), page_rank.end(), sort_pred());

  for(int i = 0; i < page_rank.size(); i++){
    cout << page_rank[i].first << " " << page_rank[i].second << endl;
  }

  return 0;
}


