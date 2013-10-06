#include<iostream>
#include<fstream>
#include<iomanip>
#include<queue>
// limit of unsigned int

using namespace std;

int vCount, nEdges;

struct nodeDistance
{
  int node;
  long int distance;
};

class Comparator
{
  public:
    bool operator()(nodeDistance& n1, nodeDistance& n2)
    {
      if (n1.distance > n2.distance) 
        return true;
      else
        return false;
    }
};

void dijkstra(int s, vector< vector<int> > graph, vector < vector<int> > weight) 
{
  int mini;
  bool *visited = new bool [vCount];
  long int *dist = new long int [vCount];

  for (int i = 0; i < vCount;i++) {
    dist[i] = 9999999999;
    visited[i] = false;
  }

  dist[s] = 0;
  priority_queue< nodeDistance, vector< nodeDistance >, Comparator> pq;

  nodeDistance first = {s,0};
  pq.push(first);

  while(!pq.empty())
  {
    nodeDistance temp = pq.top();
    pq.pop();
    int node= temp.node;
    cout << "processing node" << node << endl;

    for(int i=0;i < graph[node].size();i++)
    {
      if(dist[graph[node][i]] > (dist[node] + weight[node][i]))
        dist[graph[node][i]] = dist[node] + weight[node][i];

      if(!visited[graph[node][i]])
      {
        cout << "adding node " << i << " to the queue" << endl;
        nodeDistance newNode;
        newNode.node=graph[node][i];
        newNode.distance=dist[graph[node][i]];
        pq.push(newNode);
        visited[graph[node][i]]=true;
      }
    }
  }

  cout << "The shortest distance from " << s << " to all the nodes is" << endl;
  for(int i=0;i < vCount;i++)
  {
    cout << i << "," << dist[i] << endl;
  }
  cout << endl << endl;
}

int main(int argc, char **argv){
  int src, dst, wght;
  int sourceNode;
  sourceNode = atoi(argv[2]);

  char *filename = argv[1];
  cout << "reading file" << endl;

  ifstream read(filename);
  read >> vCount >> nEdges;

  vector< vector<int> > graph(vCount);
  vector< vector<int> > weight(vCount);

  while(read >> src >> dst >> wght){
    graph[src].push_back(dst);
    weight[src].push_back(wght);
  }

  dijkstra(sourceNode, graph, weight);
  return 0;
}
