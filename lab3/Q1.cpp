#include <bits/stdc++.h>
using namespace std;

// function that converts the string to integer
int s_t(string s){
    stringstream ney(s);
    int ans = 0;
    ney >> ans;
    return ans;
}
 
void new_edges( map<int,set<int>> &adjList,vector<pair<int,int>> &edges,int &n){
    
    for(auto x : edges){
         adjList[x.first].insert(x.second);
         adjList[x.second].insert(x.first);
         n = max({n,x.first,x.second});
    }

}

// function that read the given input graph and stores the edge list
void readGraph(vector<pair<int,int>> &edges){
  string line;
  ifstream myfile ("graph-1.txt");
  if (myfile.is_open()){
    while ( getline (myfile,line) ){
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

int set_inter(set<int>a, set<int>b){
  int cou = 0;
    for(auto i: a){
        if(b.find(i)!= b.end()){
          cou ++;
        }
    }
    return cou;
}

void calmax(map<int,set<int>>& adjList, map<int,int>& deg,int &maxin, int &maxout){
    for(auto it: adjList){
        int inn = 0 , outt = 0;
        int count = deg[it.first];
        for(auto it1: it.second){
            int itd = deg[it1];
            if(itd > count){
                outt++;
            }
            else if(itd < count){
                inn++;
            }
            else{
                if(it.first > it1){
                    inn++;
                }
                else{
                    outt++;
                }
            }
        }
        maxin = max(maxin,inn);
        maxout = max(maxout,outt);
    }
}

//function that counts the number of triangles in the graph
void triangles(map<int,set<int>> adjList,map<int,int> &tri){
    for(auto it : adjList){

        for(auto j : it.second ){
            tri[it.first] += set_inter(it.second,adjList[j]);
        }
    }
}

void couDeg(map<int,set<int>> adjList,map<int,int>&deg){
    for(auto i:adjList){
        deg[i.first] = i.second.size(); 
    }
}

void couGen(map<int,set<int>> adjList,map<int,int>&gen,map<int,int>deg){
    for(auto i:adjList){
        int cou = INT_MIN;
        for(auto j: i.second){
            cou = max(cou,deg[j]);
        }
        gen[i.first] = cou;
    }
}

int main(){ 
    int N = 1;
    vector<pair<int,int>>edges;
    map<int,set<int>> adjList;
    readGraph(edges);
    
    new_edges(adjList,edges,N);
    map<int,int> deg;
    couDeg(adjList, deg);

    int maxin_degree = INT_MIN;
    int maxout_degree = INT_MIN;
    calmax(adjList, deg, maxin_degree, maxout_degree);
    cout<<"Using vertex degree, The maximum indegree is "<<maxin_degree<<" The maximum outdegree is "<<maxout_degree<<endl;
    map<int,int>tri;
    triangles(adjList,tri);
    int maxin = INT_MIN;
    int maxout = INT_MIN;
    calmax(adjList,tri,maxin,maxout);
    cout << "Using the number of triangles contained per vertex, the maximum indegree is "<<maxin<< " and maximum out degree is " <<maxout<<endl;
    couDeg(adjList,deg);

    map<int,int>gen;
    couGen(adjList,gen,deg);

    maxin = INT_MIN;
    maxout = INT_MIN;
    calmax(adjList,gen,maxin,maxout);
    cout <<"Using graph degeneracy the maximum indegree is "<< maxin << " and maximum out degree is "<<maxout << endl;

    

}