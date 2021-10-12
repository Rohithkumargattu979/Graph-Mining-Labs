#include<bits/stdc++.h>
using namespace std;


int stringtoint(string s){ 
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}
void read_names(map<int,vector<string>>&mp){
  string line;
  ifstream myfile("facebook_target.txt");
  int c = 0;
    if(myfile.is_open()){
        while(getline(myfile,line)){
          if(c==0){
            c++;
            continue;
          }
            int n = line.length();
            string id = "";
            string fb_id = "";
            string page_name = "";
            string page_type = "";
            int count = 0;
            for(int i=0; i<n; i++){
                if(line[i]==',')count++;
                if(line[i] != ',' and count == 0){
                    id += line[i];
                }
                if(line[i] != ',' and count == 1){
                    fb_id += line[i];
                }
                if(line[i] != ',' and count == 2){
                    page_name += line[i];
                }
                if(line[i] != ',' and count == 3){
                    page_type += line[i];
                }
               
            }
            vector<string>vs;
            vs.push_back(fb_id);
            vs.push_back(page_name);
            vs.push_back(page_type);
            int k = stringtoint(id);
            mp[k] = vs;
        }
    }
    else{
        cout<<"Cannot open the file "<<endl;
    }
}

void read_graph(vector<pair<int,int>> &edges,int &N_NODES){
  string line;
  ifstream myfile ("facebook_edges.txt");
  int c = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    { 
         if(c==0){
           c++;
           continue;
         }
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
         N_NODES =  max(N_NODES,max(u,v));
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
    
}

void addEdge(  map<int,vector<float>>&graph, vector<pair<int,int>>edges,vector<int>&out_degree){
    for(int i=0; i<edges.size(); i++){
       int u,v;
       u = edges[i].first;
       v = edges[i].second;
       graph[v].push_back(u);
       out_degree[u]++;
    }
}

bool mycompare( pair<float,int>a, pair<float,int>b ){
   if(a.first > b.first){
     return true;
   }    
   return false;
}

int main(){
    vector<pair<int,int>> edges;
    int N_NODES = 0;
    read_graph(edges,N_NODES);
    map<int,vector<float>>graph;
    vector<int>out_degree(N_NODES+1,0);
    addEdge(graph,edges,out_degree);
    vector<float>pagerank(N_NODES+1,1.0);
     map<int,vector<string>>mp;
     read_names(mp);
  
    do{
      float curr,latest,ans = 0.0;
      for(int i=0;i<=N_NODES;i++){
       float sum = 0.0 ; curr = pagerank[i];
        for(int j=0;j<graph[i].size();j++){
           sum += pagerank[graph[i][j]]/(out_degree[graph[i][j]]) ;
        }
       pagerank[i]  =  0.15*(1.0) + 0.85*sum;
       latest = pagerank[i];
     }

     float diff = abs(curr - latest);
     ans += diff;
     if(ans < 0.000000001)break;
    } while(1);
    
    vector<pair<float,int>>v;
    for(int i=0;i<=N_NODES;i++){
      pair<float,int>p;
      p.second = i;
      p.first = pagerank[i];
      v.push_back(p);
    }
    sort(v.begin(),v.end(),mycompare);
    cout<<"ID"<<"       "<<"Page_rank"<<"    "<<"Page_Name"<<"   "<<endl;

    for(int i=0;i<10;i++){
      cout<<v[i].second<<"    "<<pagerank[v[i].second]<<"    "<<mp[v[i].second][1]<<"    "<<endl;
    }
 

   

}
