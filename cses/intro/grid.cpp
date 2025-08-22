#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> in(n);
    for(int i = 0; i < n; i++){
        cin >> in[i];
    }

    vector<string> out(n, string(m, '?'));
    const vector<char> C = {'A','B','C','D'};

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // collect forbidden letters
            bool forbid[4] = {false,false,false,false};
            // 1) original
            for(int z = 0; z < 4; z++){
                if (C[z] == in[i][j]) forbid[z] = true;
            }
            // 2) above
            if (i > 0) {
                for(int z = 0; z < 4; z++){
                    if (C[z] == out[i-1][j]) forbid[z] = true;
                }
            }
            // 3) left
            if (j > 0) {
                for(int z = 0; z < 4; z++){
                    if (C[z] == out[i][j-1]) forbid[z] = true;
                }
            }
            // pick any allowed
            bool placed = false;
            for(int z = 0; z < 4; z++){
                if (!forbid[z]) {
                    out[i][j] = C[z];
                    placed = true;
                    break;
                }
            }
            // (by pigeonhole there is always at least one)
            if (!placed) {
                // should never happen
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    // print
    for(int i = 0; i < n; i++){
        cout << out[i] << "\n";
    }
    return 0;
}


// always an option w