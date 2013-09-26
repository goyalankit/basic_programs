#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class Vertex{
  public:
    Vertex();

    int outDegree;
    int weight;
    vector<Vertex*> inverteces;
    int nodeNumber;
};

//initialize the out degree vertices
Vertex::Vertex(){
  outDegree = 0;
}

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

int main(int argc, char** argv ){
  int Vcount = 23947346;
  vector<Vertex> Graph(Vcount);
  vector<double> page_rank_previous(Vcount, 1.0/Vcount);
  vector<double> page_rank_next(Vcount,0.0);

  double tolerence = 99999.9999;
  float damping_factor = 0.85;
  double temp, constant_part;
  //reading the file and building the graph
  int source, destination;
  ifstream read("road2");

  while(read >> source >> destination){
    Graph[source].outDegree++;
    Graph[source].nodeNumber = source;
    Graph[destination].nodeNumber = destination;
    Graph[destination].inverteces.push_back(&Graph[source]);
  }



   /*
    *for(int m=0; m<Graph.size();m++){
    *  cout << Graph[m].outDegree << endl;
    *  for(int j=0; j<Graph[m].inverteces.size(); j++){
    *    cout << "node numbers for node " << m << " are " << Graph[m].inverteces[j]->nodeNumber << endl;
    *  }
    *}
    */



//  cout << Graph[0].inverteces[0] -> nodeNumber;
//  cout << Graph[0].inverteces[0] -> outDegree;

  while(tolerence > .0001){
    constant_part = ((1.0 - damping_factor));
    tolerence = 99999.999;


    for(int i=0;i<Vcount;i++){
      temp = 0.0;
      for(int j=0; j<Graph[i].inverteces.size(); j++){

     //   cout <<  "for active node" <<  i <<"node number " <<  Graph[i].inverteces[j] -> nodeNumber << " outdegree" << Graph[i].inverteces[j] -> outDegree <<  endl;
        temp += (page_rank_previous[Graph[i].inverteces[j] -> nodeNumber] / Graph[i].inverteces[j] -> outDegree);
      }
      page_rank_next[i] = constant_part + (damping_factor *  temp);
  //    cout << "node "  << i <<  "temp " << temp << endl;
   //   cout << "final contribution from neighouring nodes" << page_rank_next[i] << endl;
      tolerence = covergence_degree(page_rank_next, page_rank_previous);
//      cout << tolerence << " ";
    }
  for(int k =0; k < page_rank_next.size(); k++){

//    cout << "previous page rank values" <<  page_rank_previous[k] << "next page rank " << page_rank_next[k] << endl;
  }

  for(int k =0; k < page_rank_next.size(); k++){
    page_rank_previous[k] = page_rank_next[k];
  }
}


  for(int k=0; k<Vcount; k++){
    cout << "PageRank for node " << k << " is " << page_rank_next[k] << endl;
  }

  return 0;
}
