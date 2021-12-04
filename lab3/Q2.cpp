#include <bits/stdc++.h>
using namespace std;

map<pair<int,int>,int>weights;
int N;
// map<int,int>leafs;
// set<int> leaf_node;
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
    string file = "graph-3.txt";
    ifstream myfile("graph-3.txt");
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
            N = max(n1,n2);
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

// // Returns and assigns the edge value from parent to present 
// int recurse(map<int,vector<int>> adjlist, int present, int parent, map<pair<int,int>,float> &edge_values, const vector<int> node_values, set<int> &leaf_node){
//     if(leaf_node.find(present) == leaf_node.end()){
//         int child_sum = 0;

//         for (auto neighbour : adjlist[present]){
//             child_sum += recurse(adjlist, neighbour, present, edge_values, node_values,leaf_node);
//         }

//         edge_values[{parent, present}] = (float)(1 + child_sum) / node_values[present];  
//         return edge_values[{parent, present}];
//     }
//     else {
//         edge_values[{parent, present}] = (float)node_values[parent] / node_values[present];
//         return edge_values[{parent, present}];
//     } 
// }




vector<int> enumerate(map<int,vector<int>> adjlist, int start, int n, set<int> &leaf_node){
       queue<int>q;
       q.push(start);
       vector<int> weight(n+1,0);
       vector<int> visited(n+1,0);
       visited[start] = 0;
       weight[start] = 1;
       while(!q.empty()){
            int p = q.front();
            q.pop();
            int old_q = q.size();
            for(auto x : adjlist[p]){
                weight[x] += weight[p];                                                                                                                                                                                                    
                if(!visited[x]){
                    visited[x] = 1;
                    q.push(x);
                }
            }
            if(old_q == q.size()) 
                leaf_node.insert(p);
       }
       weight[start] = 0;
       return weight;
}

void counter(map<int,vector<int>> adjlist, int n, map<pair<int,int>,float> &edge_values, const vector<int> node_values, set<int> &leaf_node){
    queue<int>q;
    vector<int>visited(n+1,0);
    for(auto x:leaf_node){
        q.push(x);
        visited[x] = 1;
    }
    vector<int>v(n+1,0);
    map<pair<int,int>,float>edge_weights;
    map<int,int>
    while(!q.empty()){
        int k = q.front(); q.pop();
        for(auto x : adjlist[k]){
                 v[x]++;
                 if(adjlist[x].size() == v[x]){
                     if(leaf_node.find(k)!=leaf_node.end()){
                               edge_weights[make_pair(k,x)] = (float) node_values[x]/node_values[k] ;
                               edge_weights[make_pair(x,k)] = (float) node_values[x]/node_values[k] ;
                     }
                     else{
                               edge_weights[make_pair(k,x)] = (float)(1 + )/node_values[k];
                     }
                     
                 }
                     
                          if(visited[x]==0){
                              visited[x]=1;
                              q.push(x);
                          }
        }
    }
}

void init(map<int,vector<int>> adjlist, int n){
    map<pair<int,int>,float> edge_values;
    for(int i=1;i<=n;i++){
        edge_values.clear();
        set<int> leaf_node;
        vector<int> node_values = enumerate(adjlist,i,n, leaf_node);
        //recurse(adjlist, i, i, edge_values, node_values, leaf_node);
        counter(adjlist, n, edge_values, node_values, leaf_node);

    }
    for(auto x : edge_values){
        weights[{x.first.first,x.first.second}] += x.second;
    }
}

void dfs(map<int,vector<int> > adjList , vector<int>&visited, int k){
    visited[k] = 1;
    for(auto x:adjList[k]){
         if(visited[x]==0){
           dfs(adjList,visited,x);
       }
    }
}

int number_of_components( map<int,vector<int> > adjList , int n){
    vector<int>visited(n+1,0);
    int count = 0;
    for(int i=1;i<=n;i++){
       if(visited[i]==0){
           count++;
           dfs(adjList,visited,i);
       }
    }
    return count;
}



int main(){
    vector<vector<int> > edges;
    map<int,vector<int> > adjList;
    readGraph(edges);
    addEdge(adjList,edges);
    init(adjList,N);
   // cout<<number_of_components(adjList,N);
   //cout<<edges.size()<<" "<<N;
}