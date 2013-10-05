#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>
#include <algorithm>

using namespace std;

struct timeval start, end;

int vCount, nEdges, sourceNode;

struct Edge
{
  public:
    int source;
    int destination;
    int weight;

};

void print_shortest_path(int dist[]){
  for(int i=0; i< vCount ; i++){
    cout << i << " " << dist[i] << endl;
  }
}

int main(int argc, char **argv){
  if(argc < 3){
    cout << "Usage: ./a.out <filename(string)> <source(int)>" << endl;
    exit(0);
  }

  int src, dst, wght;
  sourceNode = atoi(argv[2]);

  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read(filename);
  read >> vCount >> nEdges;

  vector< vector<int> > graph(vCount);
  vector< vector<int> > weight(vCount);
  int degree[vCount], dist[vCount];

  for(int i=0;i<vCount;i++){
    dist[i]=99;
    degree[i]=0;
  }
  dist[sourceNode] = 0;

  while(read >> src >> dst >> wght){
    graph[src].push_back(dst);
    weight[src].push_back(wght);
  }

  gettimeofday(&start, NULL); //start time of the actual page rank algorithm
  int destination;
  bool relaxed = false;
  for(int i=0; i < vCount ; i++ ){
    relaxed = false;
    for(int j=0; j< vCount ; j++){
      for(int k=0; k < graph[j].size(); k++){
        destination = graph[j][k];
        if(dist[j] + weight[j][k] < dist[destination]){
          dist[destination] = dist[j] + weight[j][k];
          relaxed = true;
        }
      }
    }
    if(relaxed == false)
      break;
  }
  gettimeofday(&end, NULL); //page rank ends here
  cout << "Time taken by parallel execution on " << argv[2] << " threads and " << vCount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;

  print_shortest_path(dist);
  return 0;
}
