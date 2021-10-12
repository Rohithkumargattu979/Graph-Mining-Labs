#include <bits/stdc++.h>
using namespace std;

class CSR{
  public:
  vector<int>A,JA,IA;
};

bool operator<(pair<int,int> e1, pair<int,int>  e2) {
	return e1.first<e2.first || (e1.first==e2.first && e1.second<e2.second);
}

typedef map<int,int> MII;
typedef vector<int> VI;
typedef MII::iterator EdgeIter;

const int maxClass=1000;

ifstream fin;
ofstream fout;
string infile, outfile;

int n, m;
VI mapto;
VI bin;
vector<pair<int,int>> binEdge;
vector<VI> A;
vector<MII> CSRrep, pos;

int cntClass[maxClass];
int stringtoint(string s){ 
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}
CSR* CSR_graph = new CSR;
inline bool compVertex(int i, int j) {
	return CSR_graph->IA[i]-CSR_graph->IA[i-1]<CSR_graph->IA[j]-CSR_graph->IA[j-1] || (CSR_graph->IA[i]-CSR_graph->IA[i-1]==CSR_graph->IA[j]-CSR_graph->IA[j-1] && i<j);
}

inline void orderPair(int &u, int &v) {
	if (!compVertex(u,v)) swap(u,v);
}

inline void printClass(int u, int v, int cls) {
	++cntClass[cls];
	fout << "(" << u << "," << v << "):" << cls << endl;
}

inline void updateSupport(int u, int v, int delta) {
	CSRrep[u][v]+=delta;
	CSRrep[v][u]+=delta;
}

inline void removeEdge(int u, int v) {
	CSRrep[u].erase(v);
	CSRrep[v].erase(u);
}

vector<pair<int,int>>edges;
void add_edges( map<int,vector<int>> &graph_adj_list,vector<pair<int,int>> &edges){
    
    for(auto x : edges){
         graph_adj_list[x.first].push_back(x.second);
         graph_adj_list[x.second].push_back(x.first);
    }

}
void initialize_CSR(CSR* CSR_graph,int n,map<int,vector<int>> &graph_adj_list){
 
  for(int i=0;i<2*m;i++){
    CSR_graph->A.push_back(1);
   }
   
   CSR_graph->IA.push_back(0);
   int prev = 0;  
   for(auto x : graph_adj_list){
      int u = x.first;
      vector<int> v = x.second;
      for(int j=0;j<v.size();j++)
      CSR_graph->JA.push_back(v[j]);
      CSR_graph->IA.push_back(prev + v.size());
      prev += v.size();
  }

}

void readGraph() {
  string line;
  ifstream myfile ("graph-1.txt");
  
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
		 n = max(n,max(u+1,v+1));
    }
	m = edges.size();
	CSRrep.resize(n);
    myfile.close();
	
	for (int i=0; i<n; ++i) CSRrep[i].clear();
	for (auto x:edges) {
		int u = x.first;
		int v = x.second;
		if (u==v) continue;
		if (CSRrep[u].find(v)==CSRrep[u].end()) {
			CSRrep[u][v]=0;
			CSRrep[v][u]=0;
		}
	}
  }

  else cout << "Unable to open file"; 
	
}

void reorder() {
	mapto.resize(n);
	for (int i=0; i<n; ++i) mapto[i]=i;
	sort(mapto.begin(), mapto.end(), compVertex);
}

void intersect(const VI &a, const VI &b, VI &c) {
	c.clear();
	unsigned j=0;
	for (unsigned i=0; i<a.size(); ++i) {
		while (j<b.size() && b[j]>a[i]) ++j;
		if (j>=b.size()) break;
		if (b[j]==a[i]) c.push_back(a[i]);
	}
}

void countTriangles() {
	A.resize(n);
	for (int i=0; i<n; ++i) A[i].clear();
	int nDeltas=0;
	for (int vi=n-1; vi>=0; --vi) {
		int v=mapto[vi];
		for (EdgeIter it = CSRrep[v].begin(); it!=CSRrep[v].end(); ++it) {
			int u = it->first;
			if (!compVertex(u,v)) continue;
			VI common;
			intersect(A[u], A[v], common);
			for (unsigned i=0; i<common.size(); ++i) {
				int w=mapto[common[i]];
				++nDeltas;
				updateSupport(u,v,1);
				updateSupport(v,w,1);
				updateSupport(w,u,1);
			}
			A[u].push_back(vi);
		}
	}
	fout << nDeltas << " triangles found.\n";
}

void binSort() {
	bin.clear(); bin.resize(n,0);
	int nBins=0;
	int mp=0;
	for (int u=0; u<n; ++u) {
		MII tadj = CSRrep[u];
		for (EdgeIter it=tadj.begin(); it!=tadj.end(); ++it) {
			int v=it->first;
			if (!compVertex(u,v)) continue;
			int sup=it->second;
			if (sup==0) {
				printClass(u,v,2);
				removeEdge(u,v);
				continue;
			}
			++mp;
			++bin[sup];
			nBins=max(sup,nBins);
		}
	}
	m=mp;
	++nBins;
	int count=0;
	for (int i=0; i<nBins; ++i) {
		int binsize=bin[i];
		bin[i]=count;
		count+=binsize;
	}
	pos.clear(); pos.resize(n);
	for (int i=0; i<n; ++i) pos[i].clear();
	binEdge.resize(m);
	for (int u=0; u<n; ++u)
		for (EdgeIter it=CSRrep[u].begin(); it!=CSRrep[u].end(); ++it) {
			int v=it->first;
			if (!compVertex(u,v)) continue;
			int sup=it->second;
			pair<int,int> e={u,v};
			int &b=bin[sup];
			binEdge[b]=e;
			pos[u][v]=b++;
		}
	for (int i=nBins; i>0; --i) bin[i]=bin[i-1];
	bin[0]=0;
}

void updateEdge(int u, int v, int minsup) {
	orderPair(u,v);
	int sup=CSRrep[u][v];
	if (sup<=minsup) return;
	int p=pos[u][v];
	int posbin=bin[sup];
	pair<int,int> se=binEdge[posbin];
	pair<int,int> e={u,v};
	if (p!=posbin) {
		pos[u][v]=posbin;
		pos[se.first][se.second]=p;
		binEdge[p]=se;
		binEdge[posbin]=e;
	}
	++bin[sup];
	updateSupport(u,v,-1);
}

void trussDecomp() {
	for (int s=0; s<m; ++s) {
		int u=binEdge[s].first;
		int v=binEdge[s].second;
		orderPair(u,v);
		int supuv=CSRrep[u][v];
		printClass(u,v,supuv+2);
		int nfound=0;
		for (EdgeIter it=CSRrep[u].begin(); it!=CSRrep[u].end(); ++it) {
			if (nfound==supuv) break;
			int w=it->first;
			if (w==v) continue;
			if (CSRrep[v].find(w)!=CSRrep[v].end()) {
				++nfound;
				updateEdge(u,w,supuv);
				updateEdge(v,w,supuv);
			}
		}
		removeEdge(u,v);
	}
}

int main() {
	
    infile="graph-1.txt";
	outfile="graph-out.txt";
	fin.open(infile.c_str());
	fout.open(outfile.c_str());
    vector<pair<int,int>> edges;
	map<int,vector<int>> graph_adj_list;
    initialize_CSR(CSR_graph,n,graph_adj_list);
	readGraph();
	add_edges(graph_adj_list,edges);
	reorder();
	countTriangles();
	binSort();
	trussDecomp();

	for (int i=0;i<maxClass; ++i)
		if (cntClass[i]>0)
			fout << "#edges in " << i << "-class: " << cntClass[i] << endl;

	fin.close();
	fout.close();

	return 0;
}
