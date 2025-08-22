#include <bits/stdc++.h>
using namespace std;

bool freeCell[8][8];
bool col[8], d1[15], d2[15];
int ans = 0;

// Try to place a queen in row r
void dfs(int r) {
    if (r == 8) {
        ++ans;
        return;
    }
    for (int c = 0; c < 8; c++) {
        if (!freeCell[r][c]) continue;           // reserved
        if (col[c] || d1[r+c] || d2[r-c+7]) continue; 
        // place queen at (r,c)
        col[c] = d1[r+c] = d2[r-c+7] = true;
        dfs(r+1);
        col[c] = d1[r+c] = d2[r-c+7] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 8; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 8; j++) {
            freeCell[i][j] = (s[j] == '.');
        }
    }

    dfs(0);
    cout << ans << "\n";
    return 0;
}
