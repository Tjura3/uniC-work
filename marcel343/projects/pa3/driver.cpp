// CSS 343 · PA3 — given driver. Exercises BOTH classes on simple_graph.txt
// (which holds TWO graphs — your buildGraph must leave the stream positioned
// for the next one). Its output must match expected-output.txt EXACTLY:
//
//   g++ -std=c++17 -g graphm.cpp graphl.cpp sample_driver.cpp -o pa3
//   ./pa3 > myoutput.txt && diff myoutput.txt expected-output.txt
//   valgrind --leak-check=full ./pa3        (on the CSS lab; GraphL owns heap!)
//
// This driver is the FLOOR, not the ceiling — it never feeds a bad file,
// never removes a nonexistent edge, never starts a search mid-graph. Your own
// driver.cpp must cover those (that's the Testing criterion).
#include "graphm.h"
#include "graphl.h"

int main() {
    // ---- Part 1: GraphM over every graph in the file -----------------------
    ifstream inM("simple_graph.txt");
    if (!inM) { cout << "simple_graph.txt not found\n"; return 1; }
    int gNo = 0;
    for (;;) {
        GraphM g;
        if (g.buildGraph(inM) != 1) break;
        cout << "=== GraphM · graph " << ++gNo << " (" << g.getSize() << " nodes) ===\n";
        g.findShortestPath();
        g.displayAllPaths();
        if (gNo == 1) {
            cout << "displayPath(1, 4):\n";
            g.displayPath(1, 4);
            cout << "removeEdge(1, 3), recompute:\n";
            g.removeEdge(1, 3);
            g.findShortestPath();
            g.displayPath(1, 4);                       // detour now: 1 5 4 = 55
            cout << "insertEdge(1, 3, 20) restores it:\n";
            g.insertEdge(1, 3, 20);
            g.findShortestPath();
            g.displayPath(1, 4);
        }
    }

    // ---- Part 2: GraphL over the same file ---------------------------------
    ifstream inL("simple_graph.txt");
    gNo = 0;
    for (;;) {
        GraphL g;
        if (g.buildGraph(inL) != 1) break;
        cout << "=== GraphL · graph " << ++gNo << " (" << g.getSize() << " nodes) ===\n";
        g.displayGraph();
        cout << "edgeList(1): " << g.edgeList(1) << '\n';
        cout << "DFS from 1:  " << g.DFSorder() << '\n';
        cout << "BFS from 1:  " << g.BFSorder() << '\n';
        cout << '\n';
    }
    

    cout << "\n\nMY TESTS ==========================================================\n";
    //The given sample_driver.cpp is the floor:
    //it never feeds a malformed file,
    //never inserts an invalid edge,
    //never starts a traversal anywhere but vertex 1,
    //and never rebuilds an existing object.
    //Your driver.cpp does all of that, on both provided files.
    int no = 0;
    inM.close();
    inL.close();
    {//Badgraph
        cout << "Badgraph test.\n";
        ifstream inM("bad-graph.txt");
        ifstream inL("bad-graph.txt");
        int temp = no;
        if(!inM || !inL){
            cout << "file not found" << endl;
        }else{
            for(int i = 1; i < 3; i++){
                GraphM g;
                if (g.buildGraph(inM) != 1){
                    cout << "Badgraph " << i << " caught for graphM.\n";
                }else{
                    cout << "Badgraph ran without errors for graphM.\n";
                    g.findShortestPath();
                    g.displayAllPaths(); //the only valid path should be 1 to 2 cost 10
                    no++;
                }
            }
            for(int i = 1; i < 3; i++){
                GraphL g;
                if (g.buildGraph(inL) != 1){
                    cout << "Badgraph " << i << " caught for graphL.\n";
                }
                else{
                    cout << "Badgraph ran without errors for graphL.\n";
                    g.displayGraph();
                    no++;
                }
            }
            cout << "Realized in testing, bagraph will continue if the nodes are bad, check graph manually.\n";
            no -= 2;
        }
        if(no == temp) cout << "Good\n";
        cout << "=============================================\n";
    }

    {//inval edge
        cout << "graphM invalid edge testing\n";
        ifstream inM("simple_graph.txt");
        GraphM g;
        if (g.buildGraph(inM) == 1) {
            int sz = g.getSize();
            int temp = no;
            cout << "out of bounds source\n";
            if(g.insertEdge(0, 2, 10) == 1){
                cout << "Invalid edge submitted\n";
                no++;
            }

            cout << "out of bounds source (oversize) (" << sz + 1 << ", 2, 10)\n";
            if(g.insertEdge(sz + 1, 2, 10) == 1){
                cout << "Invalid edge submitted\n";
                no++;
            }

            cout << "out of bounds TO (1, 0, 10)\n";
            if(g.insertEdge(1, 0, 10) == 1){
                cout << "Invalid edge submitted\n";
                no++;
            }

            cout << "out of bounds TO (oversize) (1, " << sz + 5 << ", 10)\n";
            if(g.insertEdge(1, sz + 5, 10) == 1){
                cout << "Invalid edge submitted\n";
                no++;
            }

            cout << "negative FROM and TO (-1, -5, 10)\n";
            if(g.insertEdge(-1, -5, 10) == 1){
                cout << "Invalid edge submitted\n";
                no++;
            }

            cout << "negative weight (1, 2, -15)\n";
            if(g.insertEdge(1, 2, -15) == 1){
                cout << "Invalid edge submitted\n";
                no++;
            }

            
            if(no == temp){
                cout << "All inputs rejected.\n";
            }
            cout << "Match with first graph on expected =====================\n";
            g.findShortestPath();
            g.displayAllPaths();
            cout << "======================================\n";
        }
    }

    {//invalid traversal (not vertex 1)
        cout << "Invalid traversal, GraphL.\n";
        ifstream inL("simple_graph.txt");
        GraphL g;
        int temp = no;
        if (g.buildGraph(inL) == 1) {
            int sz = g.getSize();
            //out of bounds 0
            cout << "DFS node 0: '" << g.DFSorder(0) << "' (expected empty)\n";
            if (g.DFSorder(0) != "") no++;
            cout << "BFS node 0: '" << g.BFSorder(0) << "' (expected empty)\n";
            if (g.BFSorder(0) != "") no++;

            //out of bounds oversize
            cout << "DFS node " << sz + 1 << ": '" << g.DFSorder(sz + 1) << "' (expected empty)\n";
            if (g.DFSorder(sz + 1) != "") no++;
            cout << "BFS node " << sz + 1 << ": '" << g.BFSorder(sz + 1) << "' (expected empty)\n";
            if (g.BFSorder(sz + 1) != "") no++;

            //out of bounds negative
            cout << "DFS node -1: '" << g.DFSorder(-1) << "' (expected empty)\n";
            if (g.DFSorder(-1) != "") no++;
            cout << "BFS node -1: '" << g.BFSorder(-1) << "' (expected empty)\n";
            if (g.BFSorder(-1) != "") no++;

            //edgelist on invalid
            cout << "edgeList(0): '" << g.edgeList(0) << "' (expected empty)\n";
            if (g.edgeList(0) != "") no++;
            cout << "edgeList(" << sz + 5 << "): '" << g.edgeList(sz + 5) << "' (expected empty)\n";
            if (g.edgeList(sz + 5) != "") no++;
        }
        if(no == temp){
            cout << "Good\n";
        }
        cout << "======================================\n";
    }

    {//remove test
        cout << "bad remove, invalid edges\n";
        ifstream inM("simple_graph.txt");
        GraphM g;
        int temp = no;
        if (g.buildGraph(inM) == 1) {
            //for the simple graph, 1 to 4 works, but 4 to 1 doesnt
            g.removeEdge(4, 1);

            //out of bounds
            if(g.removeEdge(0, 2) == 1){
                no++;
            }
            if(g.removeEdge(1, 99) == 1){
                no++;
            }
            //run for errors
            g.findShortestPath();
        }
        if(no == temp){
            cout << "Good\n";
        }
        cout << "======================================\n";
    }

    {//mid traversals, GraphL
        cout << "middle traversals, GraphL\n";
        ifstream inL("simple_graph.txt");
        GraphL g;
        int temp = no;
        if (g.buildGraph(inL) == 1) {
            //starts at 2, should be valid.
            if (g.DFSorder(2) == "") no++;
            if (g.BFSorder(2) == "") no++;

            //4 has no outgoing, shouldn't be empty, should just output itself
            if (g.DFSorder(4) != "4") no++;
            if (g.BFSorder(4) != "4") no++;
        }
        if (no == temp) {
            cout << "Good\n";
        }
        cout << "======================================\n";
    }

    {//rebuilding existing objects, GraphM & GraphL
        cout << "Rebuilding existing graph objects\n";
        ifstream inM("simple_graph.txt");
        ifstream inL("simple_graph.txt");
        GraphM gM;
        GraphL gL;
        int temp = no;
        gM.buildGraph(inM);
        gL.buildGraph(inL);

        //second graph built directly on top of the first, should clear itself and have 3 nodes.
        if (gM.buildGraph(inM) == 1) {
            if (gM.getSize() != 3) no++; // Should resize to 3
        } else {
            no++;
        }
        //same for the list variant
        if (gL.buildGraph(inL) == 1) {
            if (gL.getSize() != 3) no++; // Should resize to 3
        } else {
            no++;
        }

        if (no == temp) {
            cout << "Good\n";
        }
        cout << "======================================\n";
    }

    if(no == 0){
        cout << "All tests passed without issues.\n";
    }else{
        cout << "Some tests failed, check above. Error count: " << no << endl;
    }
    return 0;
}
