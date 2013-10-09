#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>
#include <algorithm>
#include<queue>
#include<tr1/unordered_set>
#include<tr1/unordered_map>

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


bool bucket_not_empty(vector < tr1::unordered_set <int> >  buckets){
  for(int i=0; i < buckets.size(); i++){
    if(buckets[i].size()!=0){
      return true;
    }
  }
  return false;
}

void print_shortest_path(long int dist[]){
  for(int i=0; i< vCount ; i++){
    cout << i << " " << dist[i] << endl;
  }
}


int main(int argc, char **argv){
  if(argc < 4){
    cout << "Usage: ./a.out <filename(string)> <source(int)> <thread-count(int)>" << endl;
    exit(0);
  }

  int delta = 10;

  int src, dst, wght;
  sourceNode = atoi(argv[2]);

  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read(filename);
  read >> vCount >> nEdges;

  //  vector< vector<int> > buckets(2);
  vector < vector<int> > outVertices(vCount);
  vector< tr1::unordered_map<int, int> > weight(vCount);

  int maxWeight = 0;

  while(read >> src >> dst >> wght){
    weight[src][dst] = wght;
    outVertices[src].push_back(dst);

    if(wght > maxWeight){
      maxWeight = wght;
    }
  }


  long int dist[vCount];
  for(int n=0;n<vCount;n++){
    dist[n]=9999999;
  }

  dist[sourceNode] = 0;
  cout << maxWeight;
  tr1::unordered_set <int> bucket;
  //  vector< queue<int> > buckets(vCount);

  int node, destination, new_bucket_number;
  bool relaxed = false;
  Edge edge;
  cout << "bucket size " << bucket.size() << endl;
  bucket.insert(sourceNode);

  gettimeofday(&start, NULL); //start time of the actual page rank algorithm

  vector<int> requests, deletedNodes;
    while(!bucket.empty()){
      node = (*bucket.begin());
      bucket.erase(node);
      for(int i = 0; i < outVertices[node].size(); i++ ){
         if(dist[node] + weight[node][outVertices[node][i]] < dist[outVertices[node][i]]){
          dist[outVertices[node][i]] = dist[node] + weight[node][outVertices[node][i]];
          int y = dist[outVertices[node][i]];
          bucket.insert(outVertices[node][i]);
        }
      }

  }

  gettimeofday(&end, NULL); //page rank ends here
  cout << "Time taken by sequential execution chaotic relaxation " << vCount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;


  print_shortest_path(dist);
  return 0;
}
