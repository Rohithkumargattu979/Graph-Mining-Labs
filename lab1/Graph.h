#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include <queue>
#include <utility>

using namespace std;

class Graph {
  int numberOfVertices;
  vector< vector<int> > adjList;

  vector<int> getDistanceFromU(int u);
  int computeMaxEccentricity(set<int> vertices);
  vector< set<int> > computeF(int u);
  int getVertexWithMaximumDegree();
  int maxDistantVertex(int u);
  int midVertex(int u, int v);

  public:
  int computeEccentricity(int u);
  Graph(int numberOfVertices);
  void addEdge(int u, int v);
  int iFUB(int u, int l, int k);
  pair<int, int> fourSweep();
};

#endif
