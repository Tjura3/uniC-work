// CSS 343 · PA3 — GraphL implementation SKELETON. Every method is a TODO.
#include "graphl.h"
#include <stack>
#include <queue>

GraphL::GraphL() {}

GraphL::~GraphL() {
    // TODO: delete every EdgeNode in every list, then the node array.
    //       valgrind must report zero leaks after the driver runs.
    clear();
}
void GraphL::clear(){
    if(nodeArray != nullptr){
        for(int i = 1; i <= size; i++){
            EdgeNode* curr = nodeArray[i].edgeHead;
            while(curr != nullptr){
                EdgeNode* temp = curr->nextEdge;
                delete curr;
                curr = temp;
            }
            nodeArray[i].edgeHead = nullptr;
        }
        delete[] nodeArray;
        nodeArray = nullptr;
    }
    size = 0;
}
void GraphL::clearVisited(){
    for(int i = 1; i <= size; i++){
        nodeArray[i].visited = false;
    }
}
int GraphL::buildGraph(ifstream& file) {
    // TODO: free any current graph first (buildGraph may be called again);
    //       read n, allocate nodeArray[n+1], getline the names; read edge
    //       triples until the 0 line, IGNORING the weight, inserting each
    //       EdgeNode AT THE HEAD of its list.
    //(void)file;
    //return -1;
    clear(); //clear current
    //Pulled from graphM
    int n = 0; //amount of vertacies
    if(!(file >> n) || n <= 0) return -1; //fail is negative 1
    size = n;
    nodeArray = new GraphNode[size+1]; //size + 1 because 1 indexed

    string clear;
    getline(file, clear); //I wish there was a better way to do this in the standard library...
    for(int i = 1; i <= size; i++){
        getline(file, nodeArray[i].data);
    }
    int from = 0;
    int to = 0;
    int cost = 0;
    while(file >> from && from != 0){
        file >> to;
        file >> cost;
        if(from < 1 || from > size || to < 1 || to > size) continue;
        EdgeNode* newE = new EdgeNode; //newEdge
        newE->adjGraphNode = to;
        
        newE->nextEdge = nodeArray[from].edgeHead;
        nodeArray[from].edgeHead = newE;
    }
    getline(file, clear);
    return 1;
}

int GraphL::getSize() const { return size; }

string GraphL::edgeList(int nodeId) const {
    //(void)nodeId;
    //return "";    // TODO: adjacent ids in list order, space-separated
    if(nodeId < 1 || nodeId > size) return "";
    string res = ""; //result
    EdgeNode* curr = nodeArray[nodeId].edgeHead;
    bool first = true; 
    while(curr != nullptr){
        if(!first){
            res += " ";
        }
        res += to_string(curr->adjGraphNode);
        first = false;
        curr = curr->nextEdge;
    }
    return res;
}

int GraphL::displayGraph() const {
    // TODO: "Graph:" then per node: "Node i      name" and one
    //       "  edge i j" line per EdgeNode, in list order (see expected-output.txt)
    //return -1;
    if(size <= 0 || nodeArray == nullptr) return -1;
    cout << "Graph:\n";

    for(int i = 1; i <= size; i++){
        cout << "Node " << left << setw(7) << i << nodeArray[i].data << endl;
        EdgeNode* curr = nodeArray[i].edgeHead;
        while(curr != nullptr){
            cout << "  edge " << i << " " << curr->adjGraphNode << endl;
            curr = curr->nextEdge;
        }
    }
    return 1;
}

string GraphL::DFSorder(int start) {
    // TODO: ITERATIVE with an explicit stack — push start; pop u (skip if
    //       visited), visit it, push u's neighbors in list order. Recursion
    //       is not accepted here.
    //(void)start;
    //return "";
    if(start < 1 || start > size || nodeArray == nullptr) return "";
    clearVisited();

    string res = "";
    stack<int> s;
    s.push(start);
    bool first = true;
    while(!s.empty()){
        int u = s.top();
        s.pop();
        if(nodeArray[u].visited) continue;
        nodeArray[u].visited = true;
        if(!first){
            res += " ";
        }
        res += to_string(u);
        first = false;

        EdgeNode* curr = nodeArray[u].edgeHead;
        while(curr != nullptr){
            if(!nodeArray[curr->adjGraphNode].visited){
                s.push(curr->adjGraphNode);
            }
            curr = curr->nextEdge;
        }
    }
    return res;
}

string GraphL::BFSorder(int start) {
    // TODO: queue; mark visited when you ENQUEUE (not dequeue).
    //(void)start;
    //return "";
    if(start < 1 || start > size || nodeArray == nullptr) return "";
    clearVisited();

    string res = "";
    queue<int> q;
    q.push(start);
    nodeArray[start].visited = true;
    bool first = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();

        
        
        if(!first){
            res += " ";
        }
        res += to_string(u);
        first = false;

        EdgeNode* curr = nodeArray[u].edgeHead;
        while(curr != nullptr){ //push each edge into the q
            int adj = curr->adjGraphNode;
            if(!nodeArray[adj].visited){
                nodeArray[adj].visited = true;
                q.push(adj);
            }
            curr = curr->nextEdge;
        }
    }
    return res;
}
