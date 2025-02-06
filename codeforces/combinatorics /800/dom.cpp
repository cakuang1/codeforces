#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using ll = long long;
using ld = long double;
const ll mod = 1e9 + 7;
const ll N = 2e5 + 10;
const ll inf = 1e9;
const ll linf = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    while (t--) {
        int n, k1, k2;
        cin >> n >> k1 >> k2;
        int w, b;
        cin >> w >> b;

        // Calculate the total number of available pairs for white and black cells
        int totalWhiteCells = k1 + k2;
        int totalBlackCells = 2 * n - k1 - k2;

        // Number of white dominoes that can be formed
        int maxWhiteDominoes = totalWhiteCells / 2;
        // Number of black dominoes that can be formed
        int maxBlackDominoes = totalBlackCells / 2;

        // Check if we can place the required number of white and black dominoes
        if (w <= maxWhiteDominoes && b <= maxBlackDominoes) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
