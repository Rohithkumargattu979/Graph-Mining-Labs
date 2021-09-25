/*

Graph reader that reads the edge list from an edge list file and stores the graph in Adjacency List.
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
    ifstream myfile("graph-1.txt");
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
void addEdge(map<int,vector<int> >& adjList, vector<vector<int> >& edges){
    for(int i=0; i<edges.size(); i++){
        adjList[edges[i][0]].push_back(edges[i][1]);
        adjList[edges[i][1]].push_back(edges[i][0]);
    }
}
int main(){
    vector<vector<int> > edges;
    map<int,vector<int> > adjList;
    readGraph(edges);
    addEdge(adjList,edges);
}
