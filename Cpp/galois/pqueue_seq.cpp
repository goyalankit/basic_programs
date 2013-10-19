#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

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

    for (int i = 0; i < componentId.size(); i++) {
        std::cout << componentId[i] << std::endl;
    }
}

