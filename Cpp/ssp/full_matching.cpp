#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>
#include <algorithm>

using namespace std;

struct Edge
{
  public:
    int source;
    int destination;
    int weight;

};

bool present_in_working_set(vector< vector<Edge> > working_set,Edge edge, int j){
  for(int k=0; k < working_set[j].size();k++){
    if(working_set[j][k].source == edge.source || working_set[j][k].source == edge.destination || working_set[j][k].destination == edge.destination || working_set[j][k].destination == edge.source){
      return true;
    }
  }
  return false;
}

vector< vector<Edge> > maximal_matching(vector<Edge> edges){
  vector< vector<Edge> > working_set(2);
  bool added = false;
  for(int i=0; i< edges.size();i++){
    added = false;
    for(int j=0; j < working_set.size(); j++){
      if(!present_in_working_set(working_set, edges[i], j)){
        working_set[j].push_back(edges[i]);
        added = true;
        break;
      }
    }

    if(added == false){
      working_set.resize(working_set.size() + 1);
      working_set[working_set.size()-1].push_back(edges[i]);
    }
  }
  return working_set;
}

void print_maximal_matching(vector< vector<Edge> > working_set){
  for(int i=0; i< working_set.size(); i++){
    for(int j=0; j < working_set[i].size();j++){
      cout << i << " " << working_set[i][j].source << " -> " << working_set[i][j].destination << endl;
    }
  }
}


int main(int argc, char **argv){

  vector<Edge> edges;

  if(argc < 3){
    cout << "Usage: ./a.out <filename(string)> <thread-count(int)>" << endl;
    exit(0);
  }

  int src, dst, wght;
  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read(filename);
  while(read >> src >> dst >> wght){
    Edge edge;
    edge.destination = dst;
    edge.weight = wght;
    edge.source = src;
    edges.push_back(edge);
  }

  vector< vector<Edge> > working_set;
  working_set = maximal_matching(edges);

  print_maximal_matching(working_set);

  return 0;
}
