#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<cmath>
#include<sys/time.h>

using namespace std;

struct timeval start, end;

void write_page_rank_to_file(vector<double> page_rank){
  ofstream myfile("pr_serial_two_copy_values.txt");
  if(myfile.is_open()){
    for(int k=0; k<page_rank.size(); k++){
      myfile << k << " " << page_rank[k] << "\n";
    }
    myfile.close();
  }
}

int main(int argc, char** argv ){

  if(argc < 2){
    cout << "Missing filename!" << endl;
    cout << "Usage: ./a.out <filename(string)>" << endl;
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

  double tolerence = 1, temp, constant_part;
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
  gettimeofday(&start, NULL);
  constant_part = ((1.0 - damping_factor)/Vcount);

  //running the actual page rank algorithm
  while(tolerence > .0001 and iterations < 100){
    tolerence = 0.0;
    for(int i=0;i<Vcount;i++){
      temp = 0.0;
      for(int j=0; j < inVertices[i].size(); j++){
        temp += page_rank_previous[inVertices[i][j]] / outDegree[inVertices[i][j]];
      }
      page_rank_next[i] = constant_part + (damping_factor *  temp);
    }

    for(int k =0; k < Vcount; k++){
      tolerence += abs(page_rank_next[k] - page_rank_previous[k]);
      page_rank_previous[k] = page_rank_next[k];
    }
    cout << tolerence;
    iterations++;
    cout << "iteration number " << iterations << endl;
  }
  gettimeofday(&end, NULL);
  cout << "Time taken by serial execution for " << Vcount << " nodes is " << (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << endl;
//  write_page_rank_to_file(page_rank_next); uncomment this line to print page rank to a file
  return 0;
}
