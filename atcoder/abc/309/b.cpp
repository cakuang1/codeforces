
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    for (auto &s : a) cin >> s;

    vector<string> b = a;

    // Top row: move right
    for (int j = 0; j < n - 1; j++) {
        b[0][j + 1] = a[0][j];
    }

    // Right column: move down
    for (int i = 0; i < n - 1; i++) {
        b[i + 1][n - 1] = a[i][n - 1];
    }

    // Bottom row: move left
    for (int j = 1; j < n; j++) {
        b[n - 1][j - 1] = a[n - 1][j];
    }

    // Left column: move up
    for (int i = 1; i < n; i++) {
        b[i - 1][0] = a[i][0];
    }

    for (auto &s : b) {
        cout << s << '\n';
    }

    return 0;
}
