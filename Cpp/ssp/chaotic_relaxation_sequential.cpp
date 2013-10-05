#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>
#include <algorithm>
#include<queue>
#include<tr1/unordered_set>

using namespace std;

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

void print_shortest_path(int dist[]){
  for(int i=0; i< vCount ; i++){
    cout << i << " " << dist[i] << endl;
  }
}


int main(int argc, char **argv){
  if(argc < 4){
    cout << "Usage: ./a.out <filename(string)> <source(int)> <thread-count(int)>" << endl;
    exit(0);
  }

  int delta = 3;

  int src, dst, wght;
  sourceNode = atoi(argv[2]);

  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read(filename);
  read >> vCount >> nEdges;

//  vector< vector<int> > buckets(2);
  vector < vector<int> > lightEdges(vCount);
  vector < vector<int> > heavyEdges(vCount);
  vector< vector<int> > weight(vCount, vector<int>(vCount));

  int maxWeight = 0;

  while(read >> src >> dst >> wght){
    weight[src][dst] = wght;
    if(wght < delta)
      lightEdges[src].push_back(dst);
    else
      heavyEdges[src].push_back(dst);

    if(wght > maxWeight){
      maxWeight = wght;
    }
  }


  int dist[vCount];
  for(int n=0;n<vCount;n++){
    dist[n]=maxWeight + 10;
  }

  dist[sourceNode] = 0;
  cout << maxWeight;
  vector < tr1::unordered_set <int> > buckets(maxWeight + 10);
//  vector< queue<int> > buckets(vCount);

  int node, destination, new_bucket_number;
  bool relaxed = false;
  Edge edge;
  cout << "bucket size " << buckets.size() << endl;
  buckets[0].insert(sourceNode);

  vector<int> requests, deletedNodes;
  while(bucket_not_empty(buckets)){
    for(int i=0; i<buckets.size();i++){
      while(!buckets[i].empty()){
        node = (*buckets[i].begin());
        buckets[i].erase(node);
        deletedNodes.push_back(node);

        for(int j=0; j<lightEdges[node].size();j++){
          int x = dist[lightEdges[node][j]];
          if(dist[node] + weight[node][lightEdges[node][j]] < dist[lightEdges[node][j]]){
            dist[lightEdges[node][j]] = dist[node] + weight[node][lightEdges[node][j]];
            int y = dist[lightEdges[node][j]];
            buckets[x/delta].erase(lightEdges[node][j]);
            buckets[y/delta].insert(lightEdges[node][j]);
          }
        }
      }

      for(int k=0;k<deletedNodes.size();k++){
          node = deletedNodes[k];
        for(int j=0;j<heavyEdges[node].size();j++){
          cout << "node " << k << endl; 
        int x = dist[heavyEdges[node][j]];
          if(dist[node] + weight[node][heavyEdges[node][j]] < dist[heavyEdges[node][j]]){
            dist[heavyEdges[node][j]] = dist[node] + weight[node][heavyEdges[node][j]];
            int y = dist[heavyEdges[node][j]];
            buckets[x/delta].erase(heavyEdges[node][j]);
            buckets[y/delta].insert(heavyEdges[node][j]);
          }
        }
      }
      deletedNodes.clear();
    }
  }
  print_shortest_path(dist);
  return 0;
}


