#include <bits/stdc++.h>
using namespace std;

int ans[8][8];
int dx[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
int dy[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

bool dfs(int r, int c, int move) {
    ans[r][c] = move;
    if (move == 64) return true;

    // Collect all unvisited neighbors
    vector<pair<int,pair<int,int>>> nbr;
    nbr.reserve(8);
    for(int i = 0; i < 8; i++){
        int nr = r + dy[i];
        int nc = c + dx[i];
        if (nr<0||nr>=8||nc<0||nc>=8||ans[nr][nc]!=0) continue;
        // Count onward moves from (nr,nc)
        int cnt = 0;
        for(int j = 0; j < 8; j++){
            int rr = nr + dy[j], cc = nc + dx[j];
            if (rr>=0&&rr<8&&cc>=0&&cc<8&&ans[rr][cc]==0) cnt++;
        }
        nbr.push_back({cnt,{nr,nc}});
    }
    // Warnsdorff’s rule: try smallest cnt first
    sort(nbr.begin(), nbr.end());

    for(auto &p : nbr){
        int nr = p.second.first, nc = p.second.second;
        if (dfs(nr, nc, move+1)) return true;
    }

    // backtrack
    ans[r][c] = 0;
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    cin >> x >> y;
    // input (x,y): x=column [1..8], y=row [1..8]
    int sr = y-1, sc = x-1;

    // initialize
    memset(ans, 0, sizeof(ans));

    // run search
    dfs(sr, sc, 1);

    // print the board: row by row
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << ans[i][j] << (j+1<8?' ':'\n');
        }
    }
    return 0;
}


