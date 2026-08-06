// CSS 343 · PA3 — Part 4 graph generator (GIVEN).
//   g++ -std=c++17 -O2 gen_graphs.cpp -o gen && ./gen
// Writes dense_V.txt and sparse_V.txt for V = 200, 400, 800, 1600 in the PA3
// file format (fixed seed — everyone measures the same graphs):
//   dense:  every ordered pair gets an edge with probability 1/2  (E ~ V^2/2)
//   sparse: 4 out-edges per vertex                                 (E ~ 4V)
// Race your two Dijkstras over these: GraphM's O(V^2) scan (all-pairs) vs
// your ICA 09 heap version looped over every source. Doubling table per
// family; the crossover is the report's centerpiece.
#include <fstream>
#include <string>
#include <chrono>
#include "graphm.h"

#define ICA09_GRADER
#include "ica09.cpp"
using namespace std;
using namespace chrono;

//for ICA9
WGraph buildWGraph(const string& filename) {
    ifstream file(filename);
    int n;
    file >> n;
    WGraph g(n + 1);
    string dummy;
    getline(file, dummy);
    for (int i = 1; i <= n; ++i) getline(file, dummy);

    int u, v, w;
    while (file >> u && u != 0) {
        file >> v >> w;
        g.addEdge(u, v, w);
    }
    return g;
}

int main() {
    unsigned s = 343;
    auto rnd = [&]() { s = s * 1103515245u + 12345u; return (s >> 16) % 32768u; };
    for (int V : {200, 400, 800, 1600}) {
        for (int dense = 0; dense < 2; dense++) {
            ofstream f((dense ? "dense_" : "sparse_") + to_string(V) + ".txt");
            f << V << '\n';
            for (int i = 1; i <= V; i++) f << "v" << i << '\n';
            if (dense) {
                for (int u = 1; u <= V; u++)
                    for (int v = 1; v <= V; v++)
                        if (u != v && rnd() % 2 == 0)
                            f << u << ' ' << v << ' ' << (1 + rnd() % 99) << '\n';
            } else {
                for (int u = 1; u <= V; u++)
                    for (int k = 0; k < 4; k++) {
                        int v = 1 + (int)(rnd() % V);
                        if (v != u) f << u << ' ' << v << ' ' << (1 + rnd() % 99) << '\n';
                    }
            }
            f << "0 0 0\n";
        }
    }

    //race
    cout << "\n=========================================================\n";
    cout << "Type\t\tV\tGraphM (ms)\tHeap Dijkstra (ms)\n";
    cout << "=========================================================\n";

    for (int V : {200, 400, 800, 1600}) {
        for (int i = 0; i < 2; i++) {
            string filename = (i ? "dense_" : "sparse_") + to_string(V) + ".txt";
            
            ifstream fileM(filename);
            GraphM gM;
            gM.buildGraph(fileM);
            fileM.close();

            auto startM = high_resolution_clock::now();
            gM.findShortestPath();
            auto endM = high_resolution_clock::now();
            double timeM = duration<double, milli>(endM - startM).count();

            // --- Benchmark ICA 09 (Heap Dijkstra looped over all V sources) ---
            WGraph gW = buildWGraph(filename);

            auto startHeap = high_resolution_clock::now();
            for (int src = 1; src <= V; ++src) {
                dijkstra(gW, src);
            }
            auto endHeap = high_resolution_clock::now();
            double timeHeap = duration<double, milli>(endHeap - startHeap).count();

            // --- Print Results ---
            cout << (i ? "Dense\t\t" : "Sparse\t\t")
                 << V << "\t" << timeM << " ms\t\t" << timeHeap << " ms\n";
        }
    }
    cout << "=========================================================\n";



    return 0;
}
