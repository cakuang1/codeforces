#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int H, W, D;
    cin >> H >> W >> D;
    
    // Read the grid
    vector<string> grid(H);
    for(int i=0; i<H; i++) {
        cin >> grid[i];
    }
    
    // Initialize a visited grid to track humidified cells
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    
    // Initialize a queue for BFS
    queue<pair<int, int>> q;
    
    // Enqueue all humidifier positions and mark them as visited
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            if(grid[i][j] == 'H') {
                q.push({i, j});
                visited[i][j] = true;
            }
        }
    }
    
    // Directions for moving up, down, left, right
    int dirs[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    
    // Perform BFS up to D moves
    int current_level = 0;
    while(!q.empty() && current_level < D){
        int level_size = q.size();
        for(int i=0; i<level_size; i++) {
            pair<int, int> current = q.front(); q.pop();
            int x = current.first;
            int y = current.second;
            for(int d=0; d<4; d++) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                // Check boundaries
                if(nx >=0 && nx < H && ny >=0 && ny < W){
                    // Check if the cell is a floor or humidifier and not yet visited
                    if( (grid[nx][ny] == '.' || grid[nx][ny] == 'H') && !visited[nx][ny]){
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
        current_level++;
    }
    
    // Count humidified floor cells (including 'H')
    int humidified_count = 0;
    for(int i=0;i<H;i++) {
        for(int j=0;j<W;j++) {
            if( (grid[i][j] == '.' || grid[i][j] == 'H') && visited[i][j]){
                humidified_count++;
            }
        }
    }
    
    cout << humidified_count;
    
    return 0;
}


