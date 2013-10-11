#include<iostream>
#include<limits>
#include<fstream>
#include<sys/time.h>
#include<vector>
#include<queue>
#include<tr1/unordered_set>
#include<cstring>
#include<pthread.h>
#include<stdlib.h>

#define NUM_OF_THREADS 2

using namespace std;

vector< tr1::unordered_set <int> > buckets;
vector <unsigned long int> request;
vector< vector<struct data> > lightEdges;
vector< vector<struct data> > heavyEdges;
vector< unsigned long int > dist;
unsigned long int infCheck = std::numeric_limits<unsigned long int>::max()/3;
unsigned long int total_vertices;
vector<pthread_mutex_t> locks;

struct data {
  unsigned long int destination;
  int cost;
};

struct bucketParams {
  unsigned int start;
  unsigned int end;
  int delta;
};

bool not_empty(vector< tr1::unordered_set <int> > &buckets) {
  int size1,i,j;
  size1=buckets.size();
  for(i=0;i<size1;i++) {
    if(buckets[i].size() > 0)
      return true;
  }
  return false;
}

void *delta_stepping(void* ptr) {
  unsigned long int size1,size2,i,j;
  vector<unsigned long int> removedNodes;
  pthread_mutex_t* mutex[total_vertices];
  struct bucketParams *args = (struct bucketParams *)ptr;
  int delta = args -> delta;
  for(unsigned long int t1=args->start;t1<args->end;t1++) {
    int src=request[t1];
    removedNodes.push_back(src);
    size1 = lightEdges[src].size();
    for(i=0;i<size1;i++){
      struct data d = lightEdges[src][i];
      unsigned long int initDist,finalDist;
      initDist = dist[d.destination];
      pthread_mutex_lock( &locks[d.destination] );
      if(dist[src] + d.cost < dist[d.destination]) {
        dist[d.destination] = dist[src] + d.cost;
        finalDist = dist[d.destination];
        if(initDist < infCheck)
          buckets[int(initDist/delta)].erase(d.destination);
        buckets[int(finalDist/delta)].insert(d.destination);
      }
      pthread_mutex_unlock( &locks[d.destination] );
    }

    size1 = removedNodes.size();
    for(i=0;i<size1;i++){
      unsigned long int rNode = removedNodes[i];
      size2 = heavyEdges[rNode].size();
      for(j=0;j<size2;j++){
        struct data d = heavyEdges[rNode][j];
        unsigned long int initDist,finalDist;
        initDist = dist[d.destination];
        if(dist[rNode] + d.cost < dist[d.destination]) {
          dist[d.destination] = dist[rNode] + d.cost;
          finalDist = dist[d.destination];
          if(initDist < infCheck)
            buckets[int(initDist/delta)].erase(d.destination);
          buckets[int(finalDist/delta)].insert(d.destination);
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {

  unsigned long int edges,source,destination,weight,i,j,k,sssp_for;
  std::ifstream inputfile(argv[1]);
  int delta=0,size1,size2,maxEdgeWeight,maxOutDegree;
  while (inputfile >> total_vertices >> edges) {
    break;
  }
  unsigned long int outDegree[total_vertices];
  memset( outDegree, 0, total_vertices*sizeof(unsigned long int) );
  vector<vector<unsigned long int> > out_neigh(total_vertices);
  vector<vector<unsigned long int> > out_neigh_weights(total_vertices);
  lightEdges.resize(total_vertices);
  heavyEdges.resize(total_vertices);
  dist.resize(total_vertices);
  locks.resize(total_vertices);
  buckets.resize(total_vertices);
  maxEdgeWeight = 0; maxOutDegree=0;
  while (inputfile >> source >> destination >> weight) {
    outDegree[source]++;
    if(weight > maxEdgeWeight) maxEdgeWeight = weight;
    out_neigh[source].push_back(destination);
    out_neigh_weights[source].push_back(weight);
  }
  cout<<"File reading completed and starting computation"<<endl;
  for(i=0;i<total_vertices;i++) {
    if(maxOutDegree < outDegree[i]) maxOutDegree = outDegree[i];
    locks[i] = PTHREAD_MUTEX_INITIALIZER;
  }
  delta = maxEdgeWeight/maxOutDegree;

  struct timeval start, end;
  gettimeofday(&start, NULL);
  size1 = out_neigh.size();
  for(i=0;i<size1;i++){
    size2 = out_neigh[i].size();
    for(j=0;j<size2;j++){
      struct data d;
      d.cost = out_neigh_weights[i][j];
      d.destination = out_neigh[i][j];
      if(out_neigh_weights[i][j] < delta)
        lightEdges[i].push_back(d);
      else
        heavyEdges[i].push_back(d);
    }
  }
  sssp_for = atoi(argv[1]);
  unsigned long int maxVal = std::numeric_limits<unsigned long int>::max()/2;
  for(i=0;i<total_vertices;i++) {
    dist[i] = maxVal;
  }
  dist[sssp_for] = 0;
  buckets[0].insert(sssp_for);
  k=0;
  pthread_t threads[NUM_OF_THREADS];
  while(not_empty(buckets)) {
    bucketParams params[NUM_OF_THREADS];
    while(!buckets[k].empty()) {
      while(!buckets[k].empty()) {
        int src1 = *buckets[k].begin();
        buckets[k].erase(src1);
        request.push_back(src1);
      }
      int chunk_count,current_chunk,l=0;
      chunk_count = 0;k = 0;current_chunk=0;
      unsigned long int size2 = request.size();
      int chunk_size = size2/NUM_OF_THREADS;
      int left_over = size2%NUM_OF_THREADS;
      while(l<NUM_OF_THREADS &&  chunk_count!=size2) {
        params[l].delta=delta;
        params[l].start = chunk_count;
        current_chunk = chunk_size;
        if(left_over!=0) {
          current_chunk+=1;
          left_over--;
        }
        params[l].end = chunk_count + current_chunk;
        chunk_count += current_chunk;
        pthread_create(&threads[l], NULL, delta_stepping, (void*)&params[l]);
        l++;
      }
      for(int m=0;m<l;m++) {
        pthread_join(threads[m],NULL);
      }
      request.clear();
    }
    k++;
  }
  gettimeofday(&end, NULL);
  int delta1 = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

  ofstream outputFile;
  outputFile.open ("chaotic_parallel_output");
  for(i = 0; i< total_vertices ; i++) {
    outputFile << i <<" " << dist[i] <<endl;
  }
  cout<<"Writing to output file ended"<<endl;
  return 0;
}
