#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct Node {
    int x, y, cost;
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int deltaX[4] = {0, 0, -1, 1};
int deltaY[4] = {-1, 1, 0, 0};

int getCost(char c) {
    if (c == ' ') return 1;
    if (c == 'Y') return 4;
    return INT_MAX;
}

int main() {
    vector<string> grid = {
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

    int row = grid.size();
    int column = grid[0].size();

    pair<int,int> start, end;

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(grid[i][j]=='F') start = {i,j};
            if(grid[i][j]=='%') end = {i,j};
        }
    }

    vector<vector<int>> dist(row, vector<int>(column, INT_MAX));
    vector<vector<pair<int,int>>> parent(row, vector<pair<int,int>>(column, {-1,-1}));

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    pq.push({start.first, start.second, 0});
    dist[start.first][start.second] = 0;while(!pq.empty()){
        Node current = pq.top(); pq.pop();

        if(current.cost > dist[current.x][current.y]) continue;

        for(int i=0;i<4;i++){
            int nextX = current.x + deltaX[i];
            int nextY = current.y + deltaY[i];

            if(nextX<0 || nextY<0 || nextX>=row || nextY>=column) continue;
            if(grid[nextX][nextY]=='#') continue;

            int moveCost;
            if(grid[nextX][nextY]=='%') moveCost = 1;
            else moveCost = getCost(grid[nextX][nextY]);

            int newCost = current.cost + moveCost;

            if(newCost < dist[nextX][nextY]){
                dist[nextX][nextY] = newCost;
                parent[nextX][nextY] = {current.x, current.y};
                pq.push({nextX, nextY, newCost});
            }
        }
    }

    if(dist[end.first][end.second] == INT_MAX){
        cout << "No path found\n";
        return 0;
    }

    cout << "Total cost: " << dist[end.first][end.second] << endl;

    // reconstruct path
    int x = end.first;
    int y = end.second;

    while(!(x == start.first && y == start.second)){
        auto p = parent[x][y];
        if(grid[x][y] != '%')
            grid[x][y] = '.';
        x = p.first;
        y = p.second;
    }

    // print map
    for(auto& row : grid){
        cout << row << endl;
    }

    return 0;
}