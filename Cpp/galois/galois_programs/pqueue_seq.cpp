#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<sys/time.h>

using namespace std;
struct timeval start, endf;

struct nodeComponent{
    int node;
    int componentId;
};


class Comparator
{
  public:
    bool operator()(nodeComponent& n1, nodeComponent& n2)
    {
      if (n1.componentId > n2.componentId)
        return true;
      else
        return false;
    }
};


int main(int argc, char **argv){

    bool output = false;

    if(argc < 2){
        std::cout << "No input name given." << std::endl;
        exit(0);
    }
    if(argc > 2){
        output = true;
    }

    char *filename = argv[1];

    int vCount, nEdges;
    ifstream read(filename);
    read >> vCount >> nEdges;

    int source, destination;

    /*Vector to store outgoing edges.*/
    vector< vector<int> > outgoingVertices(vCount);
    vector<int> componentId(vCount);

    //Declaring Priority queue
    priority_queue< nodeComponent, vector< nodeComponent >, Comparator> worklist;

    while(read >> source >> destination){
        outgoingVertices[source].push_back(destination);
        outgoingVertices[destination].push_back(source);
    }

    gettimeofday(&start, NULL); //start time of the actual page rank algorithm
    /*initalizing the component ids and worklist*/
    for (int i = 0; i < vCount; i++) {
        nodeComponent nd;
        nd.node = i;
        nd.componentId = i;
        componentId[i] = i;
        worklist.push(nd);
    }

    while(!worklist.empty()){
        nodeComponent node_component = worklist.top();
        worklist.pop();
        int vertex = node_component.node;

        for (int i = 0; i < outgoingVertices[vertex].size(); i++) {
            if(componentId[vertex] < componentId[outgoingVertices[vertex][i]]){
                componentId[outgoingVertices[vertex][i]] = componentId[vertex];
                nodeComponent nd;
                nd.node = outgoingVertices[vertex][i];
                nd.componentId = componentId[vertex];
                worklist.push(nd);
            }
        }
    }

    gettimeofday(&endf, NULL); //page rank ends here
    if(output){
        for (int i = 0; i < componentId.size(); i++) {
            std::cout << i <<  " " << componentId[i] << std::endl;
        }
    }

  cout << "Time taken by sequential fifo queue implementation on " << vCount << " nodes is " <<  (((endf.tv_sec  - start.tv_sec) * 1000000u +  endf.tv_usec - start.tv_usec) / 1.e6) << endl;
}

