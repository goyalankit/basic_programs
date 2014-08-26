/**
 *
 1 , 3 = 0.(3)
 2 , 4 = 0.5(0)
 22, 7 = 3.(142857)

 *
 */


#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

#define NUM_NODES 4

typedef unordered_map<string, vector<string>> Graph;

void nodesWithNoOutgoingEdges(Graph &outgoingEdges, queue<string> &Queue) {
  for (auto it = outgoingEdges.begin(), ie = outgoingEdges.end(); it != ie; ++it) {
    if ((it->second).size() == 0) {
      std::cout << "No outgoing edges:" << (it->first) << std::endl;
      Queue.push(it->first);
    }
  }
}

void removeOutgoingEdges(Graph &outgoingEdges, Graph &incomingEdges, string node) {
  // remove this node
  outgoingEdges.erase(node);

  // remove node from outgoing nodes
  vector<string> nodes = incomingEdges[node];
  for (auto &it : nodes) {
    outgoingEdges[it].erase(remove(outgoingEdges[it].begin(), outgoingEdges[it].end(), node), outgoingEdges[it].end());
  }
}

void topologicalSort(Graph &outgoingEdges, Graph &incomingEdges) {
  queue<string> *Queue = new queue<string>();
  nodesWithNoOutgoingEdges(outgoingEdges, *Queue);

  vector<string> finalOrder;

  while (!Queue->empty()) {
    string tempNode = Queue->front();
    Queue->pop();
    finalOrder.push_back(tempNode);
    removeOutgoingEdges(outgoingEdges, incomingEdges, tempNode);
    if (Queue->empty())
      nodesWithNoOutgoingEdges(outgoingEdges, *Queue);
  }

  std::cout << "---------------------" << std::endl;
  if (finalOrder.size() != NUM_NODES) {
    std::cerr << "Cycle in the dependency graph" << endl;
  //  abort();
  }
  std::cout << "---------------------" << std::endl;

  for (auto it : finalOrder) {
    std::cout << it << std::endl;
  }
}

int main(void) {

  // maintain two maps for outgoing and incoming edges.
  Graph outgoingEdges;
  Graph incomingEdges;
  outgoingEdges.insert(make_pair("a", vector<string>()));
  outgoingEdges.insert(make_pair("b", vector<string>()));
  outgoingEdges.insert(make_pair("c", vector<string>()));
  outgoingEdges.insert(make_pair("d", vector<string>()));
  outgoingEdges.insert(make_pair("e", vector<string>()));
  incomingEdges.insert(make_pair("a", vector<string>()));
  incomingEdges.insert(make_pair("b", vector<string>()));
  incomingEdges.insert(make_pair("c", vector<string>()));
  incomingEdges.insert(make_pair("d", vector<string>()));
  incomingEdges.insert(make_pair("e", vector<string>()));

  outgoingEdges["a"].push_back("b");  // a->b
  incomingEdges["b"].push_back("a");

  outgoingEdges["b"].push_back("c");  // b->c
  incomingEdges["c"].push_back("b");

  outgoingEdges["b"].push_back("d");  // b->d
  incomingEdges["d"].push_back("b");

  outgoingEdges["c"].push_back("d");  // c->d
  incomingEdges["d"].push_back("c");

  topologicalSort(outgoingEdges, incomingEdges);

  return EXIT_SUCCESS;
}

