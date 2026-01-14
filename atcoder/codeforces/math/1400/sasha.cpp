#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> b(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        // Sort bar‐positions
        sort(b.begin(), b.end());
        ll  L = (n - k + 1) / 2;
        ll  R = (n + k + 2) / 2;
        cout << b[R] - b[L] + 1 << '\n';
        
    }
    return 0;
}

