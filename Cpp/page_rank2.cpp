#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<cmath>
#include<sys/time.h>

using namespace std;

struct timeval start, end;

void write_page_rank_to_file(vector<double> page_rank){
  ofstream myfile("page_rank2.txt");
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

  vector<double> page_rank(Vcount, 1.0/Vcount);
  vector<int> outDegree(Vcount);
  vector< vector<int> > inVertices(Vcount);

  double tolerence = 1.0, temp, constant_part;
  float damping_factor = 0.85;

  //reading the file and building the graph
  ifstream read_again(filename);
  cout << "initializing graph" << endl;
  while(read_again >> source >> destination){
    outDegree[source]++;
    inVertices[destination].push_back(source);
  }
  cout << "graph initialized" << endl;

  gettimeofday(&start, NULL);
  constant_part = ((1.0 - damping_factor)/Vcount);

  double previous_page_rank_for_i=0.0;

  while(tolerence > .0001 and iterations < 100){
    tolerence = 0.0;
    for(int i=0;i<Vcount;i++){
      temp = 0.0;
      for(int j=0; j < inVertices[i].size(); j++){
        temp += page_rank[inVertices[i][j]] / outDegree[inVertices[i][j]];
      }
      previous_page_rank_for_i = page_rank[i];
      page_rank[i] = constant_part + (damping_factor *  temp);
      tolerence += abs(page_rank[i] - previous_page_rank_for_i);
    }

    iterations++;
    cout << "iteration number " << iterations << endl;
  }
  gettimeofday(&end, NULL);
  cout << "Time taken by serial execution of one copy for " << Vcount << " nodes is " << (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;

  write_page_rank_to_file(page_rank);
  return 0;
}
