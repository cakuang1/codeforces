#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<int>> grid(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char ch;
                cin >> ch;
                grid[i][j] = ch - '0';  // read as 0/1
            }
        }
        vector<int> R(n), C(n);
        for (int i = 0; i < n; i++) cin >> R[i];
        for (int j = 0; j < n; j++) cin >> C[j];

        vector<int> rowOp(n, 0), colOp(n, 0);

        // Step 1: normalize first row
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1) {
                colOp[j] ^= 1;
                for (int i = 0; i < n; i++) grid[i][j] ^= 1;
            }
        }

        // Step 2: flip rows if too heavy
        for (int i = 0; i < n; i++) {
            int rowSum = accumulate(grid[i].begin(), grid[i].end(), 0);
            if (rowSum >= (n + 1) / 2) {
                rowOp[i] ^= 1;
                for (int j = 0; j < n; j++) grid[i][j] ^= 1;
            }
        }

        // Step 3: flip cols if too heavy
        for (int j = 0; j < n; j++) {
            int colSum = 0;
            for (int i = 0; i < n; i++) colSum += grid[i][j];
            if (colSum >= (n + 1) / 2) {
                colOp[j] ^= 1;
                for (int i = 0; i < n; i++) grid[i][j] ^= 1;
            }
        }

        // Step 4: verify
        bool ok = true;
        for (int i = 0; i < n; i++) {
            int rowSum = accumulate(grid[i].begin(), grid[i].end(), 0);
            if (rowSum != R[i]) ok = false;
        }
        for (int j = 0; j < n; j++) {
            int colSum = 0;
            for (int i = 0; i < n; i++) colSum += grid[i][j];
            if (colSum != C[j]) ok = false;
        }

        if (!ok) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for (int i = 0; i < n; i++) cout << rowOp[i];
            cout << "\n";
            for (int j = 0; j < n; j++) cout << colOp[j];
            cout << "\n";
        }
    }

    return 0;
}