// computing the k - core sub graph and compute the maximum core number of graph
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

bool DFSUtil(int v, vector<bool>& visisted, vector<int>& &vDegree, int k, map<int,vector<int> >& adjList){
    visited[v] = true;
    auto it;
    for(it = adjList[v].begin(); it != adjList[v].end(); it++){
        if(vDegree[v] < k){
            vDegree[*it]--;
        }
        if(!visited[*it]){
            DFSUtil(*it,visited,vDegree,k);
        }
    }
    return (vDegree[v] < k);
}
void printKCores(int k, int V, map<int,vector<int> >& adjList, int &maximumCore){
    vector<bool> visited(V,false);
    vector<bool> processed(V,false);
    int mindeg = INT_MAX;
    int startvertex;

    vector<int> vDegree(V);
    for(int i=0; i<V; i++){
        vDegree[i] = adjList[i].size();
        if(vDegree[i] < mindeg){
            mindeg = vDegree[i];
            startvertex = i;
        }
    }
    DFSUtil(startvertex,visited,vDegree,k,adjList);

    for(int i = 0; i<V; i++){
        if(visited[i] == false){
            DFSUtil(i,visited,vDegree,k,adjList);
        }
    }
    
    cout<<"K-Cores: \n";
    for(int v=0; v<V; v++){
        if(vDegree[v] >=k){
            if(v >= maximumCore){
                maximumCore = v;
            }
            cout<<"\n["<<v<<"]";
        }


        auto it;
        for(it = adj[v].begin(); it != adj[v].end(); it++){
            if(vDegree[*it] >= k){
                cout<<"->"<<*it;
            }
        }
    }
}
int main(){
    vector<vector<int> > edges;
    map<int,vector<int> > adjList;
    readGraph(edges);
    addEdge(adjList,edges);
    int V = adjList.size();
    cout<<V<<endl;
    int k = 3;
    int maximumCore = INT_MIN;
    printKCores(k,V,adjList,maximumCore);
}
