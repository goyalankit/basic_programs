#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"
#include<cmath>
#include<sys/time.h>

using namespace std;

struct timeval start, end;

void write_page_rank_to_file(vector<double> page_rank){
	cout << "size of page rank verctor " << page_rank.size() << endl;
  ofstream myfile("pr_parallel_one_copy_values.txt");
  cout << "size of page rank vector is " << page_rank.size()<< endl;
  if(myfile.is_open()){
    for(int k=0; k< page_rank.size(); k++){
      myfile << k << " " << page_rank[k] << "\n";
    }
    myfile.close();
  }
}

int main(int argc, char** argv ){

  if(argc < 3){
    cout << "Usage: ./a.out <filename(string)> <thread-count(int)>" << endl;
    exit(0);
  }

  char *filename = argv[1];
  int source, destination, iterations=0, Vcount = 0;

  cout << "reading file and trying to find number of vertices" << endl;
  ifstream read(filename);
  while(read >> source >> destination){
    if(source > Vcount)
      Vcount = source;
    if(destination > Vcount)
      Vcount = destination;
  }

  Vcount++; //because node number starts from 0
  read.clear();

  cout << Vcount << " vertices found!" << endl;

  double tolerence = 1, constant_part;
  float damping_factor = 0.85;

  vector<double> page_rank(Vcount, 1.0/Vcount);

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

  double page_rank_previous_i=0.0;
  while(tolerence > .0001 and iterations < 100){
  tolerence = 0.0;
  omp_set_num_threads(atoi(argv[2]));
  int i,j, tid;
#pragma omp parallel for private(i,j,tid, page_rank_previous_i) shared(page_rank, Vcount, constant_part, damping_factor, inVertices, outDegree) reduction(+: tolerence)
    for(i=0;i<Vcount;i++){
      tid = omp_get_thread_num();
      page_rank_previous_i = page_rank[i];
      double temp = 0.0;
      for(j=0; j < inVertices[i].size(); j++){
        temp += page_rank[inVertices[i][j]] / outDegree[inVertices[i][j]];
      }	

      page_rank[i] = constant_part + (damping_factor *  temp);

     tolerence += abs(page_rank[i] - page_rank_previous_i);
//      cout << "thread number " << tid << endl;
 }
    iterations++;
    cout << " \n iteration number " << iterations << endl;

  }
  gettimeofday(&end, NULL); //page rank ends here

  cout << "Time taken by parallel execution with one copy on " << argv[2] << " threads and " << Vcount << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;

//  write_page_rank_to_file(page_rank); uncomment this line to print page rank values to a file
  return 0;
}
