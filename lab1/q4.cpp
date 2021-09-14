#include "Graph.h"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
// function that converts a given string to integer and returns it.
int stringtoint(string s){ 
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}
string file = "graph-1.txt";
// function that reads the .txt file which contains edge list and stores the graph in a 2-D Vector
// the given file contains edges in space-sperated format
void readGraph(vector<pair<int,int> > &edges){
    string line;
    ifstream myfile (file);
    if (myfile.is_open()){
      cout<<"Starting reading file "<<file<<"....."<<endl;
      while ( getline (myfile,line) ){
          stringstream iss(line);
          string word;
          int u,v;
          int count = 1;
          while(iss>>word) {
            if(count == 1){
                u = stringtoint(word); 
                count++; 
            }
            else if(count == 2){
                v = stringtoint(word); 
                count++;
            }  
            else{
              break;
            }
          }

          edges.push_back(make_pair(u,v));
      }
      myfile.close();
      cout<<file<<" reading completed and graph copied."<<endl;
    }
    else{
      cout<<"Cannot Open the file "<<file<<endl;
    }
     
}

// function that adds edges to the nodes, that is, it creates an adjacency list from the edges list
void addEdge(map<int,vector<int> >& adjList, vector<pair<int,int> >& edges){
    for(int i=0; i<edges.size(); i++){
        adjList[edges[i].first].push_back(edges[i].second);
        adjList[edges[i].second].push_back(edges[i].first);
    }
}

Graph::Graph(int numberOfVertices) {
  this->numberOfVertices = numberOfVertices;
  adjList.reserve(numberOfVertices+1);
}

void Graph::addEdge(int u, int v) {
  adjList[u].push_back(v);
  adjList[v].push_back(u);
}

vector<int> Graph::getDistanceFromU(int u) {
  vector<int> distanceFromU(numberOfVertices);
  vector<bool> visited(numberOfVertices, false);
  queue<int> BFSQueue;

  visited[u] = true;
  distanceFromU[u] = 0;
  BFSQueue.push(u);

  while (!BFSQueue.empty()) {
    int top = BFSQueue.front();
    BFSQueue.pop();

    for (vector<int>::iterator it=adjList[top].begin(); it!=adjList[top].end(); ++it) {
      if (!visited[*it]) {
        visited[*it] = true;
        distanceFromU[*it] = distanceFromU[top] + 1;
        BFSQueue.push(*it);
      }
    }
  }
  return distanceFromU;
}

int Graph::computeEccentricity(int u) {
  vector<int> distanceFromU = getDistanceFromU(u);
  int eccentricity = 0;
  for (vector<int>::iterator it=distanceFromU.begin(); it!=distanceFromU.end(); ++it) {
    if (*it > eccentricity) {
      eccentricity = *it;
    }
  }
  return eccentricity;
}

vector< set<int> > Graph::computeF(int u) {
  vector<int> distanceFromU = getDistanceFromU(u);
  int eccentricity = computeEccentricity(u);
  vector< set<int> > F(eccentricity+1);
  for (int i=0; i<numberOfVertices; ++i) {
    F[distanceFromU[i]].insert(i);
  }
  return F;
}

int Graph::computeMaxEccentricity(set<int> vertices) {
  int maxEccentricity = 0;
  for (set<int>::iterator it=vertices.begin(); it!=vertices.end(); ++it) {
    int eccentricity = computeEccentricity(*it);
    if (eccentricity > maxEccentricity) {
      maxEccentricity = eccentricity;
    }
  }
  return maxEccentricity;
}

int Graph::iFUB(int u, int l, int k) {
  int eccentricityU = computeEccentricity(u);
  int i = eccentricityU;
  int lb = max(eccentricityU, l);
  int ub = 2*eccentricityU;

  vector< set<int> > F = computeF(u);
  while (ub-lb>k) {
    int newLowerBound = max(lb, computeMaxEccentricity(F[i]));
    if (newLowerBound > 2*(i-1)) {
      return newLowerBound;
    } else {
      lb = newLowerBound;
      ub = 2*(i-1);
    }
    i--;
  }
  return lb;
}

int Graph::getVertexWithMaximumDegree() {
  int maxDegreeVertex = 0;
  int maxDegree = adjList[maxDegreeVertex].size();
  for (int i=0; i<numberOfVertices; ++i) {
    if (adjList[i].size() > maxDegree) {
      maxDegreeVertex = i;
      maxDegree = adjList[maxDegreeVertex].size();
    }
  }
  return maxDegreeVertex;
}

int Graph::maxDistantVertex(int u) {
  vector<int> distanceFromU = getDistanceFromU(u);
  int maxDistantVertex = u;
  int maxDistance = distanceFromU[maxDistantVertex];
  for (int i=0; i<numberOfVertices; ++i) {
    if (distanceFromU[i] > maxDistance) {
      maxDistantVertex = i;
      maxDistance = distanceFromU[maxDistantVertex];
    }
  }
  return maxDistantVertex;
}

int Graph::midVertex(int u, int v) {
  vector<int> distanceFromU(numberOfVertices);
  vector<int> parentVertex(numberOfVertices);
  vector<bool> visited(numberOfVertices, false);
  queue<int> BFSQueue;

  visited[u] = true;
  distanceFromU[u] = 0;
  parentVertex[u] = -1;
  BFSQueue.push(u);

  while (!BFSQueue.empty()) {
    int top = BFSQueue.front();
    BFSQueue.pop();

    for (vector<int>::iterator it=adjList[top].begin(); it!=adjList[top].end(); ++it) {
      if (!visited[*it]) {
        visited[*it] = true;
        distanceFromU[*it] = distanceFromU[top] + 1;
        parentVertex[*it] = top;
        BFSQueue.push(*it);
      }
    }
    if (visited[v]) {
      break;
    }
  }

  int midDistance = distanceFromU[v]/2;
  int midVertex = v;
  while (midDistance--) {
    midVertex = parentVertex[midVertex];
  }
  return midVertex;
}

pair<int,int> Graph::fourSweep() {
  int r1 = getVertexWithMaximumDegree();
  int a1 = maxDistantVertex(r1);
  int b1 = maxDistantVertex(a1);
  int r2 = midVertex(a1, b1);
  int a2 = maxDistantVertex(r2);
  int b2 = maxDistantVertex(a2);
  int u = midVertex(a2, b2);
  int lb = min(computeEccentricity(a1), computeEccentricity(a2));
  return make_pair(lb, u);
}

int main() {
  vector<pair<int,int> > edges;
  map<int,vector<int> > adjList;
  readGraph(edges);
  addEdge(adjList,edges);
  int numberOfVertices = adjList.size();
  int numberOfEdges = edges.size();
  Graph graph(numberOfVertices);
  map<int, int> vertexToIndex;
  set<int> vertices;
  int vertexIndex = 0;
  for (int i=0; i<numberOfEdges; ++i) {
    int vertex1 = edges[i].first;
    int vertex2 =  edges[i].second;
    
    if (vertices.find(vertex1)==vertices.end()) {
      vertexToIndex[vertex1] = vertexIndex++;
      vertices.insert(vertex1);
    }
    if (vertices.find(vertex2)==vertices.end()) {
      vertexToIndex[vertex2] = vertexIndex++;
      vertices.insert(vertex2);
    }
    graph.addEdge(vertexToIndex[vertex1], vertexToIndex[vertex2]);
  }

  cout<<"Starting the four sweep algorithm....."<<endl;
  pair<int,int> lowerBoundVertexPair = graph.fourSweep();
  cout<<"Completed the four sweep."<<endl;

  cout<<"Starting the iFUB algorithm....."<<endl;
  cout<<"Done with the iFUB algorithm."<<endl;
  cout<<"Diameter of the graph in file "<<file<<": "<<graph.iFUB(lowerBoundVertexPair.second, lowerBoundVertexPair.first, 0)<<endl;
}
