#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>

using namespace std;

struct timeval start, end;

/*
 * could be calculated while copying next to previous
 * double covergence_degree(vector<double> page_rank_next, vector<double> page_rank_previous){
  int len = page_rank_next.size();
  double tol=0.0, temp=0.0;

//#pragma omp parallel for shared(page_rank_next, page_rank_previous) reduction(+: tol)
  for(int i=0;i<len;i++){
	  temp = page_rank_next[i]-page_rank_previous[i];
    if(temp<0)
      tol += (-1)*temp;
    else
      tol += temp;
  }
  return tol;
}*/

void write_page_rank_to_file(vector<double> page_rank){
  ofstream myfile("page_rank_parallel.txt");
  if(myfile.is_open()){
    for(int k=0; k<page_rank.size(); k++){
      myfile << k << " " << page_rank[k] << "\n";
    }
    myfile.close();
  }
}

int main(int argc, char** argv ){

  if(argc < 3){
    cout << "Usage: ./a.out <filename(string)> <vertex-count(int)>" << endl;
    exit(0);
  }

  char *filename = argv[1];
  int source, destination, iterations=0, Vcount = 0;

  cout << "reading file and trying to find number of vertices" << endl;
  ifstream read(filename);
  while(read >> source >> destination){
    if(source > Vcount)
      Vcount = source;
    else if(destination > Vcount)
      Vcount = destination;
  }

  Vcount++; //because node number starts from 0
  read.clear();

  cout << Vcount << " vertices found!" << endl;

  double tolerence = 1, constant_part;
  float damping_factor = 0.85;

  vector<double> page_rank_previous(Vcount, 1.0/Vcount);
  vector<double> page_rank_next(Vcount,0.0);

  vector<int> outDegree(Vcount);
  vector< vector<int> > inVertices(Vcount);


  //reading the file and building the graph
  ifstream read_again(filename);
  cout << "initializing graph" << endl;
  while(read_again >> source >> destination){
    outDegree[source]++;
    inVertices[destination].push_back(source);
  }

  cout << "graph initialized" << endl;


  gettimeofday(&start, NULL); //start time of the actual page rank algorithm
  constant_part = ((1.0 - damping_factor)/Vcount);

  while(tolerence > .0001 and iterations < 100){
  tolerence = 0.0;
  omp_set_num_threads(16);
  int i,j, tid;
#pragma omp parallel for private(i,j,tid) shared(page_rank_next, page_rank_previous, Vcount, constant_part, damping_factor, inVertices, outDegree)
    for(i=0;i<Vcount;i++){
      tid = omp_get_thread_num();
      double temp = 0.0;
      for(j=0; j < inVertices[i].size(); j++){
        temp += page_rank_previous[inVertices[i][j]] / outDegree[inVertices[i][j]];
      }
      page_rank_next[i] = constant_part + (damping_factor *  temp);
    }

    double tol=0.0;
#pragma omp parallel for private(i) shared(page_rank_next, page_rank_previous, Vcount) reduction(+: tolerence)
    for(i =0; i < Vcount; i++){
      tolerence += abs(page_rank_next[i] - page_rank_previous[i]);
      page_rank_previous[i] = page_rank_next[i];
    }

    iterations++;
    cout << " \n iteration number " << iterations << endl;

  }
  gettimeofday(&end, NULL); //page rank ends here

  cout << "Time taken by parallel execution on 16 threads and " << Vcount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;

  write_page_rank_to_file(page_rank_next);
  return 0;
}
