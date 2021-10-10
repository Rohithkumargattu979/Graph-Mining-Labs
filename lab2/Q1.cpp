#include <bits/stdc++.h>
using namespace std;

int s_t(string s){
    stringstream ney(s);
    int ans = 0;
    ney >> ans;
    return ans;
}
 
void new_edges( map<int,vector<int>> &graph_adj_list,vector<pair<int,int>> &edges,int &n){
    
    for(auto x : edges){
         graph_adj_list[x.first].push_back(x.second);
         graph_adj_list[x.second].push_back(x.first);
         n = max({n,x.first,x.second});
    }

}

void graph_read(vector<pair<int,int>> &edges){
  string line;
  ifstream myfile ("graph-2.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
         stringstream iss(line);
         string word;
         int u,v;
         int count = 1;
         while(iss>>word) {
           if(count == 1){
               u = s_t(word); 
               count++; 
           }
           else if(count == 2){
               v = s_t(word); 
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

  else cout << "Unable to open file"; 
    
}
class CSR{
  public:
  vector<int>A,JA,IA;
};

int count_triples;

void initialize_CSR(CSR* CSR_graph,vector<pair<int,int>> &edges,map<int,vector<int>> &graph_adj_list){
 
  for(int i=0;i<2*edges.size();i++){
    CSR_graph->A.push_back(1);
   }
   
   CSR_graph->IA.push_back(0);
   int prev = 0;
   int i =1;
   for(auto x : graph_adj_list){
      int u = x.first;
      vector<int> v = x.second;
      for(int j=0;j<v.size();j++)
      CSR_graph->JA.push_back(v[j]);
      CSR_graph->IA.push_back(prev + v.size());
      //cout << CSR_graph->IA[i]<<endl;
      count_triples = count_triples + (v.size()*(v.size()-1))/2;
      //cout << v.size()<<" "<< x.first<<endl;
      prev += v.size();
      i++;
  }

}

int triangles(vector<pair<int,int>> &edges,int N){
        int count = 0;
        set<pair<int,int>>edge_list;
  for(auto x:edges){
    edge_list.insert(make_pair(x.first,x.second));
    edge_list.insert(make_pair(x.second,x.first));
  }
  set<pair<int,pair<int,int>>> visited;
        for(auto x:edges){
    for(int i=1;i<=N;i++){
            int arr[3] = {i,x.first,x.second};
            sort(arr,arr+3);
      if(edge_list.find(make_pair(x.first,i))!=edge_list.end() && edge_list.find(make_pair(i,x.second))!=edge_list.end() && visited.find(make_pair(arr[0],make_pair(arr[1],arr[2])))==visited.end()){
                             count++;
                             visited.insert(make_pair(arr[0],make_pair(arr[1],arr[2])));
      }
    }
  }
  return count;
}

int main()
{ 
  int N = 1;
  vector<pair<int,int>>edges;
  map<int,vector<int>> graph_adj_list;
  graph_read(edges);
  new_edges(graph_adj_list,edges,N);

  CSR* CSR_graph = new CSR;
  initialize_CSR(CSR_graph,edges,graph_adj_list);

  int m = triangles(edges,N);
  double val = 3*m;
  double cc = (val)/(double)count_triples;
  cout << m << endl;
  cout << count_triples<<endl;
  cout << cc << endl;

}

