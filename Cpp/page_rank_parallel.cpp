#include<iostream>
#include<vector>
#include<fstream>
#include "omp.h"

using namespace std;

double covergence_degree(vector<double> page_rank_next, vector<double> page_rank_previous){
  int len = page_rank_next.size();
  double tol=0.0;
  double temp;

  for(int i=0;i<len;i++){
    temp = page_rank_next[i]-page_rank_previous[i];
    if(temp<0)
      tol += (-1)*temp;
    else
      tol += temp;
  }
  return tol;
}

void write_page_rank_to_file(vector<double> page_rank){
  ofstream myfile("page_rank.txt");
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

  double tolerence = 99999.9999, temp, constant_part;
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

  tolerence = 99999.999;
  constant_part = ((1.0 - damping_factor)/Vcount);

  while(tolerence > .0001 or iterations < 99){
  omp_set_num_threads(4);
  int i,j;
#pragma omp parallel shared(inVertices, page_rank_next, page_rank_previous) private(i,j)
    for(i=0;i<Vcount;i++){
      temp = 0.0;
      for(j=0; j < inVertices[i].size(); j++){
        temp += page_rank_previous[inVertices[i][j]] / outDegree[inVertices[i][j]];
      }
      page_rank_next[i] = constant_part + (damping_factor *  temp);
      cout << omp_get_thread_num();
    }

#pragma omp barrier
#pragma omp parallel for
    for(int k =0; k < page_rank_next.size(); k++){
      page_rank_previous[k] = page_rank_next[k];
    }
    tolerence = covergence_degree(page_rank_next, page_rank_previous);
    iterations++;
    cout << "iteration number " << iterations << endl;
  }

  write_page_rank_to_file(page_rank_next);
  return 0;
}
