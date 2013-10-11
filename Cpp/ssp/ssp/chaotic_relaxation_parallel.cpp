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
#include<pthread.h>

using namespace std;

int vCount, nEdges, sourceNode;
vector < vector<int> > lightEdges;
vector < vector<int> > heavyEdges;
vector< tr1::unordered_map<int, int> > weight;


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct DataForThreads
{
  int *dist;
  vector < tr1::unordered_set <int> > buckets;
  int bucket_number;
  int thread_number;
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

void *parallel_region(void *arg);

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
  lightEdges.resize(vCount);
  heavyEdges.resize(vCount);
  weight.resize(vCount);
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
  vector < tr1::unordered_set <int> > buckets(190);
  //  vector< queue<int> > buckets(vCount);

  int node, destination, new_bucket_number;
  cout << "bucket size " << buckets.size() << endl;

  buckets[0].insert(sourceNode);

  int i=0;
  pthread_t threads[16];

  DataForThreads dft;
  dft.dist = dist;
  dft.buckets = buckets;

  while(bucket_not_empty(dft.buckets)){
    dft.bucket_number = i;
    for(int j=0;j<16;j++){
      dft.thread_number = j;
      pthread_create(&threads[j], NULL, parallel_region, &dft);
    }

    for(int j=0;j<16;j++){
      pthread_join(threads[j], NULL);
    }
    i+=1;
  }

  print_shortest_path(dft.dist);
  return 0;
}


void *parallel_region(void *arg){
  int node; int delta = 3;
  DataForThreads *inData = (DataForThreads*) arg;
  int i = inData -> bucket_number;
  int *dist = inData -> dist;
  vector < tr1::unordered_set <int> > &buckets = inData -> buckets;
  vector<int> requests, deletedNodes;
  deletedNodes.clear();
  while(!buckets[i].empty()){
    pthread_mutex_lock(&lock);
    node = (*buckets[i].begin());
    buckets[i].erase(node);
    deletedNodes.push_back(node);
    pthread_mutex_unlock(&lock);

    cout << "running for node " << node << "with " << lightEdges[node].size() << "light edges" << endl;
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
}

