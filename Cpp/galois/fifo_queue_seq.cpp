#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

int main(int argc, char **argv){
    char *filename = argv[1];

    int vCount, nEdges;
    ifstream read(filename);
    read >> vCount >> nEdges;

    int source, destination;

    /*Vector to store outgoing edges.*/
    vector< vector<int> > outgoingVertices(vCount);
    vector<int> componentId(vCount);

    //Declaring FIFO queue
    queue<int> worklist;

    while(read >> source >> destination){
        outgoingVertices[source].push_back(destination);
        outgoingVertices[destination].push_back(source);
    }

    /*initalizing the component ids and worklist*/
    for (int i = 0; i < vCount; i++) {
        componentId[i] = i;
        worklist.push(i);
    }

    while(!worklist.empty()){
        int vertex = worklist.front();
        worklist.pop();

        for (int i = 0; i < outgoingVertices[vertex].size(); i++) {
            if(componentId[vertex] < componentId[outgoingVertices[vertex][i]]){
                componentId[outgoingVertices[vertex][i]] = componentId[vertex];
                worklist.push(outgoingVertices[vertex][i]);
            }
        }

    }

    for (int i = 0; i < componentId.size(); i++) {
        std::cout << i << " " << componentId[i] << std::endl;
    }


}
