/*

Graph reader that reads the edge list from an edge list file and stores the graph in CSR.
-> The given graph is a simple undirected graph

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
void readGraph(vector<vector<int> >&edges){
    string line;
    string file = "graph-1.txt";
    ifstream myfile(file);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            int n = line.length();
            string num1 = "";
            string num2 = "";
            bool flag = false;
            for(int i=0; i<n; i++){
                if(line[i] != ' ' and !flag){
                    num1 += line[i];
                }
                else if(line[i] == ' '){
                    flag = true;
                }
                else if(line[i] != ' ' and flag){
                    num2 += line[i];
                }
            }
            vector<int> sub;
            int n1 = stringtoint(num1);
            int n2 = stringtoint(num2);
            sub.push_back(n1);
            sub.push_back(n2);
            edges.push_back(sub);
            sub.clear();
        }
    }
    else{
        cout<<"Cannot open the file "<<file<<endl;
    }
}

// function that adds edges to the nodes, that is, it creates an adjacency list from the edges list
void addEdge(map<int,vector<int> >& adjList, vector<vector<int> >& edges, int &n){
    for(int i=0; i<edges.size(); i++){
        adjList[edges[i][0]].push_back(edges[i][1]);
        adjList[edges[i][1]].push_back(edges[i][0]);
        n = max(n,max(edges[i][0],edges[i][1]));
    }
}

// function that converts a graph from Adjacency list to CSR.
void CSRAdjList(map<int,vector<int> >& adjList, vector<int>& IA, vector<int>& weights, vector<int>& JA, int no_of_edges){
    weights.resize(2*no_of_edges,1);
    map<int,vector<int> >:: iterator it;
    int temp = 0;
    IA.push_back(0);
    for(it = adjList.begin(); it != adjList.end(); it++){
        temp += it->second.size();
        IA.push_back(it->second.size());
        for(int i=0; i<it->second.size(); i++){
            JA.push_back(it->second[i]);
        }
    }
}
int main(){
    vector<vector<int> > edges;
    map<int,vector<int> > adjList;
    int n = 1;
    readGraph(edges);
    addEdge(adjList,edges,n);
    vector<int> IA;
    vector<int> weights;
    vector<int> JA;
    CSRAdjList(adjList, IA, weights, JA, edges.size());
}
