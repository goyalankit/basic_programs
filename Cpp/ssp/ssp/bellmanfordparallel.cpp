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
bool writeToFile=false;


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
  if(argc > 3){
    writeToFile = true;
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

  vector< vector<int> > schedule;

  while(read >> src >> dst >> wght){
    Edge e;
    e.source = src;
    e.destination = dst;
    e.weight = wght;
    edges.push_back(e);
  }

  gettimeofday(&start, NULL); //start time of the actual page rank algorithm


  vector<bool> visited_edge(nEdges, false);
  int k =0;
  unsigned long int edges_visited = 0;
  while(edges_visited!=edges.size()) {
    vector<bool> visited_node;
    visited_node.assign(vCount, false);
    for(int i=0;i<edges.size();i++){
      if(visited_edge[i]==0 && visited_node[edges[i].source]==0 && visited_node[edges[i].destination]==0) {
        schedule.resize(k+1);
        schedule[k].push_back(i);
        visited_node[edges[i].source] = true;
        visited_node[edges[i].destination] = true;
        visited_edge[i] = true;
        edges_visited++;
      }
    }
    k++;
  }

  int destination;
  bool relaxed = true;
  while(relaxed) {
    relaxed = false;
    for (int i = 0; i < schedule.size(); i++) {
#pragma omp parallel for
      for (int k = 0; k < schedule[i].size(); k++) {
        if(dist[edges[schedule[i][k]].source] + edges[schedule[i][k]].weight < dist[edges[schedule[i][k]].destination]){
        dist[edges[schedule[i][k]].destination] = dist[edges[schedule[i][k]].source] + edges[schedule[i][k]].weight;
        relaxed = true;
      }
      }
    }
  }
  gettimeofday(&end, NULL); //page rank ends here

  cout << "Time taken by sequential execution bellman ford on " << argv[2] << " threads and " << vCount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;

  if(writeToFile){
    ofstream myfile("bellmanfordparallel.txt");
    if(myfile.is_open()){
      for(int i=0;i < vCount;i++)
      {
        myfile << i << "," << dist[i] << "\n";
      }
      myfile.close();
    }
  }

  return 0;
}

