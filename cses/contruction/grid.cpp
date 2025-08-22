#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

// Apply rotation r (0=0°,1=90°,2=180°,3=270°) on (y,x) in an n×m grid
pii rot_map(int r, int n, int m, pii p) {
    int y = p.first, x = p.second;
    switch(r) {
        case 0: return {y, x};
        case 1: return {x, n - y + 1};
        case 2: return {n - y + 1, m - x + 1};
        case 3: return {m - x + 1, y};
    }
    return {0,0};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while(t--){
        int n,m, y1,x1,y2,x2;
        cin >> n >> m >> y1 >> x1 >> y2 >> x2;
        // parity check
        int p1 = (y1 + x1) & 1;
        int p2 = (y2 + x2) & 1;
        if ((n*m) % 2 == 0) {
            if (p1 == p2) { cout<<"NO\n"; continue; }
        } else {
            // both must lie on even‐parity color (0)
            if (p1 != 0 || p2 != 0) { cout<<"NO\n"; continue; }
        }

        // Try all 8 transforms
        bool found = false;
        vector<pii> fullpath;
        for(int k = 0; k < 8 && !found; k++){
            int r = k % 4;
            int f = k / 4;
            // dims after rotation
            int R = (r % 2 ? m : n);
            int C = (r % 2 ? n : m);
            // transform A,B
            pii A = {y1, x1}, B = {y2, x2};
            // rotate
            pii Ar = rot_map(r, n, m, A);
            pii Br = rot_map(r, n, m, B);
            // optional horizontal flip
            if (f) {
                Ar.second = C - Ar.second + 1;
                Br.second = C - Br.second + 1;
            }
            // endpoints of the snake
            pii S = {1,1};
            pii E = (C % 2 ? pii{R, C} : pii{1, C});
            bool rev = false;
            if (Ar == S && Br == E) {
                rev = false;
            } else if (Ar == E && Br == S) {
                rev = true;
            } else continue;

            // build the snake path in R×C
            vector<pii> snake;
            snake.reserve(R*C);
            for(int col = 1; col <= C; col++){
                if (col & 1) {
                    // downwards
                    for(int row = 1; row <= R; row++)
                        snake.emplace_back(row, col);
                } else {
                    // upwards
                    for(int row = R; row >= 1; row--)
                        snake.emplace_back(row, col);
                }
            }
            if (rev) reverse(snake.begin(), snake.end());

            // map back via inverse transform
            vector<pii> path;
            path.reserve(R*C);
            int r2 = (4 - r) % 4;
            for(auto &q : snake){
                int ur = q.first, vr = q.second;
                // unflip
                if (f) vr = C - vr + 1;
                // inverse rotation
                pii q0 = rot_map(r2, R, C, {ur, vr});
                // now q0 is in original (y,x) coordinates
                path.push_back(q0);
            }

            fullpath.swap(path);
            found = true;
        }

        if (!found) {
            // should not happen if parity passed
            cout<<"NO\n";
            continue;
        }

        // Output moves
        cout<<"YES\n";
        int L = fullpath.size();
        for(int i = 1; i < L; i++){
            auto [y0,x0] = fullpath[i-1];
            auto [y1,x1] = fullpath[i];
            if (y1 == y0+1) cout<<'D';
            else if (y1 == y0-1) cout<<'U';
            else if (x1 == x0+1) cout<<'R';
            else              cout<<'L';
        }
        cout<<"\n";
    }

    return 0;
}
