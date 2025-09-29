#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        ll nA, nB, nC;
        cin >> nA >> nB >> nC;

        // Step 1: use ABC contests greedily
        ll x = min({nA, nB, nC});
        nA -= x;
        nB -= x;
        nC -= x;

        // Step 2: use AAC/ACC contests
        ll y = min({nA, nC, (nA + nC) / 2});

        cout << (x + y) << "\n";
    }
    return 0;
}
