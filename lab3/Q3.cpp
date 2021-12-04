/*
C++ implementation of the Girvan-Newman algorithm for partitioning of a graph
Daniel J. Sharpe
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef vector<struct Node*> Nodes; // list of pointers to nodes contained in graph
typedef vector<pair<struct Node*, double>> nbrNodes; // list of pointers to neighbouring nodes with specified costs

// Node in the graph represented by a special data structure
struct Node {

    int node_idx; // index ("name") of node
    nbrNodes nbrnodes; // list of neighbours of the node, as pair (struct Node,cost)

    Node(int idx) : node_idx(idx) {}
};

// Graph in adjacency list (i.e. list of linked lists) representation
class Graph {

    public:

    Graph();
    ~Graph();
    void addnode(const int& node_idx);
    void addedge(const int& from_node, const int& to_node, double cost);
    void delnode(const int& node_idx);
    void deledge(const int& from_node, const int& to_node);
    bool check_node_exists(const int& node_idx);
    int find_node_idx(const int& node_idx);
    int find_nbr_idx(const int& from_node, const int& to_node);
    void print_info();

    private:

    int n_nodes, n_edges;
    Nodes nodes;
};

Graph::Graph() {

    n_nodes = 0;
    n_edges = 0;
}

Graph::~Graph() {

    for (auto v: nodes) {
        delete v; }
}

// add a node to the graph
void Graph::addnode(const int& node_idx) {

    if (check_node_exists(node_idx)) {
        throw runtime_error {"Tried to add existing node to graph"}; }
    n_nodes += 1;
    Node *v;
    v = new Node(node_idx);
    nodes.push_back(v);
}

// add an edge to the graph
void Graph::addedge(const int& from_node, const int& to_node, double cost) {

    int i,j;

    if (not check_node_exists(from_node) || not check_node_exists(to_node)) {
        throw runtime_error {"Tried to add edge to nonexistent node in graph"}; }
    n_edges += 1;
    if (from_node<=to_node) {
        i = find_node_idx(from_node);
        j = find_node_idx(to_node);
    } else if (to_node<from_node) {
        i = find_node_idx(to_node);
        j = find_node_idx(from_node); }
    Node *v = nodes[j];
    nodes[i]->nbrnodes.push_back(make_pair(v,cost));
}

// delete a node from the graph
void Graph::delnode(const int& node_idx) {

    int i = find_node_idx(node_idx);
    n_nodes -= 1;
    delete nodes[i];
    nodes.erase(nodes.begin()+i);
}

// delete an edge from the graph
void Graph::deledge(const int& from_node, const int& to_node) {

    int i, j;

    if (from_node<=to_node) {
        i = find_node_idx(from_node);
        j = find_nbr_idx(i, to_node);
    } else if (to_node<from_node) {
        i = find_node_idx(to_node);
        j = find_nbr_idx(i, from_node); }
    nbrNodes *nbrs = &(nodes[i]->nbrnodes);
    nbrs->erase(nbrs->begin()+j);
    n_edges -= 1;
}

// check that a node with index node_idx exists in the graph
bool Graph::check_node_exists(const int& node_idx) {

    for (auto v: nodes) {
        if (v->node_idx == node_idx) { return true; }
    }
    return false;
}

// given a node_idx, find its corresponding position in the graph
int Graph::find_node_idx(const int& node_idx) {

    int i = 0;
    for (auto v: nodes) {
        if (v->node_idx == node_idx) { return i; }
        i += 1;
    }
    throw runtime_error {"Tried to find a nonexistent node in graph"};
}

// given a node_idx, find its corresponding position in the nbrNodes list of a Node
int Graph::find_nbr_idx(const int& from_node, const int& to_node) {

    int i = 0;
    for (auto nbrnode: nodes[from_node]->nbrnodes) {
        Node *v = nbrnode.first;
        if (v->node_idx == to_node) { return i; }
        i += 1;
    }
    throw runtime_error {"Tried to find nonexistent edge in graph"};
}

void Graph::print_info() {

    cout << "Nodes in graph: " << n_nodes << " Edges in graph: " << n_edges << "\n";

    // print nodes
    for (int i=0;i<n_nodes;i++) {
        cout << nodes[i] << "\t" << &nodes[i] << "\t" << nodes[i]->node_idx << "\n";
    }

    // print neighbours of first node
    for (auto nbrnode: nodes[0]->nbrnodes) {
        Node *v = nbrnode.first;
        cout << " " << v->node_idx; }
    cout << "\n";

    // check if node 0 & node 7 exist
    cout << "Checking existence of nodes 0 & 7: " << check_node_exists(0) << \
            "\t" << check_node_exists(7) << "\n";

}

int main () {

    // The 7 bridges of Konigsberg - multigraph
    Graph graph1;
    for (int i=0;i<4;i++) {
        graph1.addnode(i); }
    graph1.addnode(4);
    graph1.addedge(0,4,10.);
    graph1.deledge(0,4);
    graph1.delnode(4);
    graph1.addedge(0,1,10.);
    graph1.addedge(0,1,8.);
    graph1.addedge(0,2,6.);
    graph1.addedge(0,2,5.);
    graph1.addedge(0,3,7.);
    graph1.addedge(1,3,5.);
    graph1.addedge(2,3,4.);

    graph1.print_info();

    return 0;
}