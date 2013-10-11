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

  vector< vector<int> > graph(vCount);
  vector< vector<int> > weight(vCount);
  int degree[vCount];
  long int dist[vCount];
  for(int i=0;i<vCount;i++){
    dist[i]=9999999999;
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
#pragma omp parallel for shared(dist)
    for(int j=0; j< vCount ; j++){
      for(int k=0; k < graph[j].size(); k++){
        destination = graph[j][k];
        if(dist[j] + weight[j][k] < dist[destination]){
#pragma omp atomic
          dist[destination] = dist[j] + weight[j][k];
          relaxed = true;
        }
      }
    }
    if(relaxed == false)
      break;
  }
  gettimeofday(&end, NULL); //page rank ends here
  cout << "Time taken by sequential execution bellman ford on " << argv[2] << " threads and " << vCount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;


  if(writeToFile){
    ofstream myfile("bellman_ford_seq.txt");
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
