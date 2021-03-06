/*
Code that computes the largest connected component of the graphs using DFS approach.
*/
#include<bits/stdc++.h>
using namespace std;

// function that converts a given string to integer and returns it.
int stringtoint(string s){ 
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}

// function that reads the .txt file which contains edge list and stores the graph in a 2-D Vector
// the given file contains edges in space-sperated format
void readGraph(vector<pair<int,int>> &edges){
    string line;
    string file = "graph-2.txt";
    ifstream myfile (file);
    if (myfile.is_open()){
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


// dfs function that computes the largest connected component in the given graph
void dfs(map<int,vector<int>>& adjList, vector<bool>& visited, int source, int &count){
  // Initially mark all vertices as not visited
 
    // Create a stack for DFS
    stack<int> stack;
 
    // Push the current source node.
    stack.push(source);
 
    while (!stack.empty()){
        // Pop a vertex from stack and print it
        int s = stack.top();
        stack.pop();
 
        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        if (!visited[s]){
            count++; // increase the size of the component
            visited[s] = true;
        }
 
        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        for (auto i = adjList[s].begin(); i != adjList[s].end(); ++i)
            if (!visited[*i])
                stack.push(*i);
    }
}

int main(){
    vector<pair<int,int> > edges;
    map<int,vector<int> > adjList;
    readGraph(edges);
    addEdge(adjList,edges);
    int largest_component = 0;
    int nodes = adjList.size();
    vector<bool> visited(nodes,false);
    for(int i=0; i<nodes; i++){
      int count = 0;
      if(!visited[i]){
        dfs(adjList,visited,i,count);
        largest_component = max(largest_component,count);
      }
    }
    cout<<largest_component<<endl;
}
