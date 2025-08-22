#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        ll a, b;
        cin >> n >> a >> b;
        ll d = gcd(a, b);

        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            v[i] %= d;
        }

        sort(v.begin(), v.end());
        ll res = v.back() - v.front();
        for (int i = 1; i < n; i++) {
            res = min(res, v[i-1] + d - v[i]);
        }

        cout << res << "\n";
    }
    return 0;
}  
