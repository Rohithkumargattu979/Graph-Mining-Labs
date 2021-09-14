#include <bits/stdc++.h>
#include "pbPlots.hpp"
#include "supportLib.hpp"
using namespace std;

class CSR{
  public:
  vector<int>A,JA,IA;
};

int stringtoint(string s){
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}
 
void add_edges( map<int,vector<int>> &graph_adj_list,vector<pair<int,int>> &edges,int &n){
    
    for(auto x : edges){
         graph_adj_list[x.first].push_back(x.second);
         graph_adj_list[x.second].push_back(x.first);
         n = max({n,x.first,x.second});
    }

}

string file = "graph-1.txt";
void read_graph(vector<pair<int,int>> &edges){
  string line;
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

  else cout << "Unable to open file "<<file; 
    
}

void initialize_CSR(CSR* CSR_graph,vector<pair<int,int>> &edges,map<int,vector<int>> &graph_adj_list){
 
  for(int i=0;i<2*edges.size();i++){
    CSR_graph->A.push_back(1);
  }
   
   CSR_graph->IA.push_back(0);
 
   for(auto x : graph_adj_list){
    int u = x.first;
    vector<int> v = x.second;
    for(int j=0;j<v.size();j++)
    CSR_graph->JA.push_back(v[j]);
    CSR_graph->IA.push_back(v.size());
  }

}

void plot_graph(CSR* CSR_graph,map<int,vector<int>> &graph_adj_list){
  int n = (int)graph_adj_list.size(); 
  //int n = 100;
  RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
  double xsa[n];
  double ysa[n];
  int i = 0;
  for(auto x:graph_adj_list){
    xsa[i] = x.first;
    ysa[i] = x.second.size();
    i++;
  }
  vector<double> xs(xsa, xsa+sizeof(xsa)/sizeof(double));
  vector<double> ys(ysa, ysa+sizeof(ysa)/sizeof(double));
  DrawScatterPlot(imageReference, 600, 400, &xs, &ys);
  vector<double> *pngdata = ConvertToPNG(imageReference->image);
  WriteToFile(pngdata, "example1.png");
  DeleteImage(imageReference->image);

}

int main(){ 
  int N = 1;
  vector<pair<int,int>>edges;
  map<int,vector<int>> graph_adj_list;
  read_graph(edges);
  add_edges(graph_adj_list,edges,N);

  CSR* CSR_graph = new CSR;
  initialize_CSR(CSR_graph,edges,graph_adj_list);
  plot_graph(CSR_graph,graph_adj_list);
}
