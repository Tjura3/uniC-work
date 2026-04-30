#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Step {
    int index;
    int cost;
    Step(int i, int c) : index(i), cost(c){}
    bool operator>(const Step& other) const { return cost > other.cost; }
};

class PathFinder{
    private:
    vector<char> grid;
    int rows;
    int cols;
    int start;
    int end;

    int toIndex(int r, int c) const{
        return r * cols + c; //get row by multiplying max, then finding the slot since its 1D
    }

    int getCost(char tile){
        if(tile == ' ' || tile == 'F' || tile == '%') return 1;
        if(tile == 'Y') return 4;
        return INF;
    }
    public:
    PathFinder(const vector<string>& inputMap) {
        rows = inputMap.size();
        cols = inputMap[0].size();
        grid.reserve(rows * cols);
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char cell = inputMap[r][c];
                grid.push_back(cell);
                if (cell == 'F') start = toIndex(r, c);
                if (cell == '%') end = toIndex(r, c);
            }
        }
    }
    void solve(){
        vector<int> dists(grid.size(), INF); //distances between
        vector<int> parent(grid.size(), -1); //parents of distances
        priority_queue<Step, vector<Step>, greater<Step>> pq;
        dists[start] = 0;
        pq.push(Step(start, 0));

        //up, down, left, right
        //1, 2, 3, 4
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!pq.empty()) {
            Step curr = pq.top();
            pq.pop();
            if (curr.cost > dists[curr.index]) continue;
            if (curr.index == end) break;

            int r = curr.index / cols;
            int c = curr.index % cols;

            for (int i = 0; i < 4; ++i) {
                int nextr = r + dr[i];
                int nextc = c + dc[i];

                if (nextr >= 0 && nextr < rows && nextc >= 0 && nextc < cols) {
                    int nextIndex = toIndex(nextr, nextc);
                    int weight = getCost(grid[nextIndex]);

                    if (weight != INF && dists[curr.index] + weight < dists[nextIndex]) {
                        dists[nextIndex] = dists[curr.index] + weight;
                        parent[nextIndex] = curr.index;
                        pq.push(Step(nextIndex, dists[nextIndex]));
                    }
                }

            }
        }
        if (dists[end] == INF) {
            cout << "No possible path." << endl;
            return;
        }

        int curr = parent[end];
        while (curr != -1 && curr != end) {
            grid[curr] = '.';
            curr = parent[curr];
        }

        printResults(dists[end]);
    }
    void printResults(int totalCost) const {
        cout << "Total Cost: " << totalCost << "\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << grid[toIndex(i, j)];
            }
            cout << "\n";
        }
    }

};

int main() {
    
    vector<string> map = {
        // "###############################",
        // "#F    YYYY      ##  ##  ###   #",
        // "# ##  ####   #####  ##  ##    #",
        // "# ##  ####   #####            #",
        // "# ##  ####   #####  ###  #### #",
        // "#        YYYY      ###  #### #",
        // "# #######YYYY#####  ###YY#### #",
        // "# #######YYYY#####  ###YY#### #",
        // "# ##         #####     YY     #",
        // "#            #####  ######    #",
        // "# ####              ##% ##    #",
        // "# ####YYY###  ####  ##  ##  ###",
        // "#     YYY###        ##        #",
        // "###############################"


        "###############################",
        "#F    YYYY      ##  ##  ###   #",
        "# ##  ####   #####  ##  ##    #",
        "# ##  ####   #####            #",
        "# ##  ####   #####  ###  #### #",
        "#        YYYY       ###  #### #",
        "# #######YYYY#####  ###YY#### #",
        "# #######YYYY#####  ###YY#### #",
        "# ##         #####     YY     #",
        "#            #####  ######    #",
        "# ####              ##% ##    #",
        "# ####YYY###  ####  ##  ##  ###",
        "#     YYY###        ##        #",
        "###############################"
    };

    PathFinder finder(map);
    finder.solve();

    return 0;
}