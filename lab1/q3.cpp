#include <bits/stdc++.h>
using namespace std;

int stringtoint(string s){
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}
 
 
 map<pair<int,int>,int>edge_list;
 
void add_edges( map<int,vector<int>> &graph_adj_list,vector<pair<int,int>> &edges,int &n){
    
    for(auto x : edges){
         graph_adj_list[x.first].push_back(x.second);
         graph_adj_list[x.second].push_back(x.first);
         n = max({n,x.first,x.second});
    }

}

void read_graph(vector<pair<int,int>> &edges){
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

  else cout << "Unable to open file"; 
    
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

int cycles_sizeof_four(){
   int count = 0;
   
   return count;
}



void check( bool marked[], int n, int vert, int start, int &count,int V){
	
	marked[vert] = true;

	
	if (n == 0) {

		marked[vert] = false;

		if (edge_list[make_pair(vert,start)]==1){
			count++;
			return;
		} else
			return;
	}

	
	for (int i = 0; i < V; i++)
		if (!marked[i] && edge_list[make_pair(vert,i)]==1)
			check(marked, n-1, i, start, count,V);

	
	marked[vert] = false;
}


int countCycles(map<pair<int,int>,int>edge_list, int n , int V){
	bool marked[V];
	memset(marked, 0, sizeof(marked));

	int count = 0;
	for (int i = 0; i < V - (n - 1); i++) {
		check(marked, n-1, i, i, count, V);
		marked[i] = true;
	}

	return count/2;
}



int main()
{ 
  int N = 1;
  vector<pair<int,int>>edges;
  map<int,vector<int>> graph_adj_list;
  read_graph(edges);
  add_edges(graph_adj_list,edges,N);


  for(auto x:edges){
		edge_list[make_pair(x.first,x.second)]=1;
		edge_list[make_pair(x.second,x.first)]=1;
  }

 //int m = triangles(edges,N);
 int m = countCycles(edge_list,3,N);
 cout<<"Number of cycles is "<<m<<endl;

}
