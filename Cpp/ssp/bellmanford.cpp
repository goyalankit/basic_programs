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

void print_shortest_path(long int dist[]){
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

  vector<Edge> edges;

  int degree[vCount];
  long int dist[vCount];
  for(int i=0;i<vCount;i++){
    dist[i]=9999999999;
    degree[i]=0;
  }
  dist[sourceNode] = 0;

  while(read >> src >> dst >> wght){
    Edge e;
    e.source = src;
    e.destination = dst;
    e.weight = wght;

    edges.push_back(e);
  }

  gettimeofday(&start, NULL); //start time of the actual page rank algorithm

  int destination;
  bool relaxed = false;
  while(relaxed) {
    relaxed = false;
    for (int i = 0; i < edges.size(); i++) {
      if(dist[edges[i].source] + edges[i].weight < dist[edges[i].destination]){
        dist[edges[i].destination] = dist[edges[i].source] + edges[i].weight;
        relaxed = true;
      }
    }
  }

  gettimeofday(&end, NULL); //page rank ends here
  cout << "Time taken by sequential execution bellman ford on " << argv[2] << " threads and " << vCount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;

  print_shortest_path(dist);
  return 0;
}

