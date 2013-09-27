#include<iostream>
#include<vector>
#include<fstream>

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
  int Vcount = atoi(argv[2]);

  vector<double> page_rank_previous(Vcount, 1.0/Vcount);
  vector<double> page_rank_next(Vcount,0.0);

  vector<int> outDegree(Vcount);
  vector< vector<int> > inVertices(Vcount);

  double tolerence = 99999.9999;
  float damping_factor = 0.85;
  double temp, constant_part;

  //reading the file and building the graph
  int source, destination, iterations=0;
  ifstream read(filename);

  cout << "initializing graph" << endl;
  while(read >> source >> destination){
    outDegree[source]++;
    inVertices[destination].push_back(source);
  }

  cout << "graph initialized" << endl;

  tolerence = 99999.999;
  constant_part = ((1.0 - damping_factor)/Vcount);

  while(tolerence > .0001 or iterations < 99){
    for(int i=0;i<Vcount;i++){
      temp = 0.0;
      for(int j=0; j < inVertices[i].size(); j++){
        temp += page_rank_previous[inVertices[i][j]] / outDegree[inVertices[i][j]];
      }
      page_rank_next[i] = constant_part + (damping_factor *  temp);
    }

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
