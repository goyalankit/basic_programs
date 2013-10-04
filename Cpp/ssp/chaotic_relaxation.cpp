#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>
#include <algorithm>

using namespace std;

int vCount, nEdges, sourceNode;

struct Edge
{
  public:
    int source;
    int destination;
    int weight;
};

void print_maximal_matching(vector< vector<Edge> > working_set){
  for(int i=0; i< working_set.size(); i++){
    for(int j=0; j < working_set[i].size();j++){
      cout << i << " " << working_set[i][j].source << " -> " << working_set[i][j].destination << endl;
    }
  }
}

void print_shortest_path(int dist[]){
  for(int i=0; i< vCount ; i++){
    cout << i << " " << dist[i] << endl;
  }
}

bool isEmpty(vector<int> ith_bucket){
  cout << "bucket size in empty " << ith_bucket.size() << endl;
  for(int i=0; i< ith_bucket.size(); i++){
    cout << "entered" << endl;
    if(ith_bucket[i] != -1){
      return false;
    }
  }
  return true;
}

int relax_edge(int dist[], Edge edge){
  if(dist[edge.source] + edge.weight < dist[edge.destination]){
    dist[edge.destination] = dist[edge.source] + edge.weight;
  }
  cout << "edge relaxed"<<endl;
  return edge.destination;
}


int main(int argc, char **argv){
  if(argc < 4){
    cout << "Usage: ./a.out <filename(string)> <source(int)> <thread-count(int)>" << endl;
    exit(0);
  }


  int src, dst, wght;
  sourceNode = atoi(argv[2]);

  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read(filename);
  read >> vCount >> nEdges;

  vector< vector<Edge> > graph(vCount);
  vector< vector<int> > buckets(2);

  hash<<int>> weights;
  while(read >> src >> dst >> wght){
    Edge edge;
    edge.destination = dst;
    edge.weight = wght;
    edge.source = src;
    graph[src].push_back(edge);
    
  }

  cout << "checking graph" << graph[0][0].source << endl;

  int dist[vCount];
  for(int n=0;n<vCount;n++){
    dist[n]=99;
  }

  dist[sourceNode] = 0;

  int node, destination, new_bucket_number;
  int delta = 3;
  bool relaxed = false;
  Edge edge;
  cout << "bucket size " << buckets.size() << endl;
  buckets[0].push_back(sourceNode);

  for(int i=0; i< buckets.size(); i++){
    while(!isEmpty(buckets[i])){
      cout << "is empty checked for bucket " << i << endl;
      for(int j=0; j< buckets[i].size(); j++){
        node = buckets[i][j];
        buckets[i][j] = -1;
        for(int k=0; k < graph[node].size(); k++){
          relaxed = false;
          edge = graph[node][k];
          cout  << "running for source = " << graph[node][k].source << " and destination= " << edge.destination << endl;
          if(dist[edge.source] + edge.weight < dist[edge.destination]){
            dist[edge.destination] = dist[edge.source] + edge.weight;
            relaxed = true;
            destination = edge.destination;
          }

          //destination = relax_edge(dist, graph[node][k]);
          cout << "new distance" << dist[destination] << endl;
          if(relaxed){
            new_bucket_number = dist[destination] % delta;
            if(buckets.size() < new_bucket_number ){
              buckets.resize(new_bucket_number + 1);
            }
            buckets[new_bucket_number].push_back(destination);
          }
        }
      }
    }
  }
  print_shortest_path(dist);
  return 0;
}
