// CSS 343 · PA3 — GraphM implementation SKELETON. Every method is a TODO.
#include "graphm.h"
#include <iomanip>

GraphM::GraphM() {}

int GraphM::buildGraph(ifstream& file) {
    // TODO: read n (fail -> -1); size the three tables (slot 0 unused, all
    //       adjM cells INF); getline n vertex names (they contain spaces);
    //       then read "from to cost" triples via insertEdge until a line
    //       starting with 0. LEAVE THE STREAM after that terminator line —
    //       the file may hold another graph.
    //(void)file;
    //return -1;

    int n = 0; //amount of vertacies
    if(!(file >> n) || n <= 0) return -1; //fail is negative 1
    size = n;

    vertices.assign(size + 1, "");
    adjM.assign(size + 1, vector<int>(size + 1, INF));
    pathM.assign(size + 1, vector<TableType>(size + 1));

    string clear;
    getline(file, clear); //to clear the first line
    for (int i = 1; i <= size; ++i) {
        getline(file, vertices[i]);
    }

    int from = 0;
    int to = 0;
    int cost = 0;
    while(file >> from && from != 0){
        file >> to;
        file >> cost;
        insertEdge(from, to, cost);
    }
    //getline(file, vertices[0]); //maybe this is better than using a dummy string? idk.
    //vertices[0] = "";
    //maybe not risk it on a project
    getline(file, clear); 
    //something, something, taking up more space because of a string but idk.
    return 1;
}

int GraphM::insertEdge(int from, int to, int cost) {
    // TODO: validate (1..size, no self-loop, cost >= 0) -> -1; set adjM
    if(from < 1 || from > size || to < 1 || to > size) return -1;
    if(from == to) return -1;
    if(cost < 0) return -1;
    adjM[from][to] = cost;
    return 1;
}

int GraphM::removeEdge(int from, int to) {
    // TODO: validate; reset the cell to INF
    if(from < 1 || from > size || to < 1 || to > size) return -1;
    adjM[from][to] = INF;

    return 1;
}

void GraphM::findShortestPath() {
    // TODO: for every source: reset pathM[src]; dist[src]=0; then size rounds
    //       of { linear-scan the nearest unsettled v; mark visited; relax
    //       every edge v->w, recording prev_node on improvement }.
    //       NOTE this is the O(V^2) variant — no priority queue anywhere.
    for(int src = 1; src <= size; src++){
        //reset, even though its this way on instantiation, if something gets deleted it needs to account for that.
        for(int v = 1; v <= size; v++){
            pathM[src][v].visited = false;
            pathM[src][v].dist = INF;
            pathM[src][v].prev_node = 0;
        }
        pathM[src][src].dist = 0;
        //djikstras basically, but linear scan.
        for(int i = 1; i <= size; i++){
            int unv = -1; 
            int minDist = INF;
            for(int v = 1; v <= size; v++){
                if(!pathM[src][v].visited && pathM[src][v].dist < minDist){
                    minDist = pathM[src][v].dist;
                    unv = v;
                }
            }
            //stop early if unreachable
            if(unv == -1) break;
            pathM[src][unv].visited = true;
            for(int v = 1; v <= size; v++){
                //check if the adjacent node to unvisited is connected to another node, and that distance isnt inf.
                //iterate through what we are trying to slot in basically to see if it is the lowest.
                if(!pathM[src][v].visited && adjM[unv][v] != INF){
                    int nDist = pathM[src][unv].dist + adjM[unv][v]; //new distance
                    if(nDist < pathM[src][v].dist){
                        pathM[src][v].dist = nDist;
                        pathM[src][v].prev_node = unv;
                    }
                }
            }
        }//for djikstras
    }//for source
}//fSP

int GraphM::getSize() const { return size; }

int GraphM::getDist(int from, int to) const {
    //(void)from; (void)to;
    //return INF;   // TODO (validate range; INF when unreachable)
    if(from < 1 || from > size || to < 1 || to > size) return INF;
    return pathM[from][to].dist;
}

string GraphM::pathRecurse(int src, int des) const {
    if(src == des){
        return to_string(src);
    }
    int prev = pathM[src][des].prev_node;
    if(prev == 0) return "";
    return pathRecurse(src, prev) + " " + to_string(des);
}
string GraphM::getPath(int from, int to) const {
    //(void)from; (void)to;
    //return "";    // TODO: follow prev_node back from `to`, emit "1 3 2"
    if(from < 1 || from > size || to < 1 || to > size) return "";
    if(pathM[from][to].dist == INF) return "";
    return pathRecurse(from, to);
}

void GraphM::displayAllPaths() const {
    // TODO: match expected-output.txt exactly — header line, then per source:
    //       the vertex name, then one line per destination:
    //       "    " << setw(3) << s << setw(5) << t << setw(10) << dist << "  " << path
    //       (dist column shows --- when unreachable, and that line has no path) 
    
    //Ive been trying too long trying to match the expected output in this way, ill just like, copy and paste the top part at this point, idk.
    //cout << left << setw(21) << "Description" << setw(6) << "From" << setw(4) << "To" << setw(14) << "Distance  " << "Path" << endl;
    cout << "Description          From  To  Distance  Path" << endl;

    for(int from = 1; from <= size; from++){
        cout << left << vertices[from] << endl;
        
        for(int to = 1; to <= size; to++){
            if(from == to) continue;
            //also had to add right alignment to get it like the expected output
            cout << "    " << right << setw(3) << from << setw(5) << to; //<< setw(10) << dist << "  " << path
            if(pathM[from][to].dist == INF){
                cout << setw(10) << "---" << endl;
            }else{
                cout << setw(10) << pathM[from][to].dist << "  " << left << getPath(from, to) << endl;
            }
        }
    }
    cout << endl;
}

void GraphM::pathRecurseNames(int src, int des) const{
    if(src == des){
        cout << vertices[src] << endl;
        return;
    }
    int prev = pathM[src][des].prev_node;
    if(prev == 0) return;
    pathRecurseNames(src, prev);
    cout << vertices[des] << endl;
}
void GraphM::displayPath(int src, int dest) const {
    // TODO: the same one-line format, then each path vertex's NAME on its own
    //       line, then a blank line (see expected-output.txt)
    //(void)src; (void)dest;
    if(src < 1 || src > size || dest < 1 || dest > size) return;
    cout << "    " << right << setw(3) << src << setw(5) << dest;
    if(pathM[src][dest].dist == INF){
        cout << setw(10) << "---" << endl;
        return;
    }else{
        cout << setw(10) << pathM[src][dest].dist << "  " << left << getPath(src, dest) << endl;
    }
    pathRecurseNames(src, dest);
    cout << endl;
}
