#include <bits/stdc++.h>
using namespace std;

// Pre‐tiled templates for all small remainders:
static vector<vector<vector<int>>> T = {
    // 2×3
    {{1,1,1},
     {2,3,2}},
    // 3×2
    {{1,1},
     {2,3},
     {2,3}},
    // 3×3
    {{1,1,2},
     {3,4,2},
     {3,4,4}},
    // 3×4
    {{1,1,1,2},
     {3,4,5,2},
     {3,4,5,6}},
    // 4×3
    {{1,1,2},
     {3,4,2},
     {5,6,4},
     {5,6,6}},
    // 4×5
    {{1,1,1,2,2},
     {3,4,4,5,2},
     {3,6,6,5,7},
     {8,6,9,9,7}},
    // 5×4
    {{1,1,1,2},
     {3,4,5,2},
     {3,6,5,7},
     {8,6,9,7},
     {8,9,9,4}},
    // 5×5
    {{1,1,1,2,2},
     {3,4,5,2,6},
     {3,7,5,8,6},
     {9,7,5,8,10},
     {9,11,11,10,4}}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;

        if((long long)n*m % 3 != 0 || n==1 || m==1){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        vector<vector<int>> G(n, vector<int>(m));

        int r = 0, c = 0;
        int R = n, C = m;

        // Peel off 3×m strips while R >= 6
        while(R - r >= 6){
            for(int j = 0; j < m; j += 3){
                // use the 3×3 template (T[2]) twice
                for(int di = 0; di < 3; di++){
                    for(int dj = 0; dj < 3; dj++){
                        G[r+di][j+dj] = T[2][di][dj];
                        G[r+3+di][j+dj] = T[2][di][dj]+6;
                    }
                }
            }
            r += 6;
            R -= 6;
        }

        // Peel off n×3 strips while C >= 6
        while(C - c >= 6){
            for(int i = r; i < n; i += 3){
                // use the 3×3 template (T[2]) twice, transposed
                for(int di = 0; di < 3; di++){
                    for(int dj = 0; dj < 3; dj++){
                        G[i+di][c+dj] = T[2][di][dj];
                        G[i+di][c+3+dj] = T[2][di][dj]+6;
                    }
                }
            }
            c += 6;
            C -= 6;
        }

        // Now (R,C) is in {2,3,3,4,4,5,5,5} with RC%3=0.
        // Find which template matches:
        int idx = -1;
        vector<pair<int,int>> dims = {
            {2,3},{3,2},{3,3},{3,4},{4,3},{4,5},{5,4},{5,5}
        };
        for(int k = 0; k < (int)dims.size(); k++){
            if(dims[k].first==R && dims[k].second==C){
                idx = k; break;
            }
        }
        auto &T0 = T[idx];
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                G[r+i][c+j] = T0[i][j];
            }
        }

        // Finally print
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout<<char('A' + (G[i][j]-1)%26);
            }
            cout<<"\n";
        }
    }
    return 0;
}
