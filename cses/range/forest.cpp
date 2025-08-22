#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<vector<int>> bit;
vector<string> grid;

// add +v at (r,c) in the 2D BIT
void update(int r, int c, int v) {
    for(int i = r; i <= n; i += i & -i)
        for(int j = c; j <= n; j += j & -j)
            bit[i][j] += v;
}

// sum in rectangle [1..r]×[1..c]
int query(int r, int c) {
    int s = 0;
    for(int i = r; i > 0; i -= i & -i)
        for(int j = c; j > 0; j -= j & -j)
            s += bit[i][j];
    return s;
}

// sum in arbitrary rectangle [r1..r2]×[c1..c2]
int query(int r1, int c1, int r2, int c2) {
    return query(r2,c2)
         - query(r1-1,c2)
         - query(r2,c1-1)
         + query(r1-1,c1-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    grid.resize(n+1);
    bit.assign(n+1, vector<int>(n+1, 0));

    // read initial forest and build BIT
    for(int i = 1; i <= n; i++){
        cin >> grid[i];
        grid[i] = " " + grid[i]; // 1‑index
        for(int j = 1; j <= n; j++){
            if(grid[i][j] == '*')
                update(i, j, +1);
        }
    }

    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int y, x;
            cin >> y >> x;
            // flip state at (y,x)
            if(grid[y][x] == '*'){
                grid[y][x] = '.';
                update(y, x, -1);
            } else {
                grid[y][x] = '*';
                update(y, x, +1);
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << query(y1, x1, y2, x2) << "\n";
        }
    }
    return 0;
}
