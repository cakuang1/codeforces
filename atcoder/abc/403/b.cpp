#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string T, U;
    cin >> T >> U;
    int n = T.size(), m = U.size();
    // Try placing U starting at each possible i in [0..n-m]
    for (int i = 0; i + m <= n; i++) {
        bool ok = true;
        for (int j = 0; j < m; j++) {
            // T[i+j] is either a letter that must match U[j],
            // or it is '?' and can match anything.
            if (T[i+j] != '?' && T[i+j] != U[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}

