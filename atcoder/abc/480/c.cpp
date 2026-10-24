#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K, T;
    cin >> N >> K >> T;

    vector<ll> A(N);
    for (ll &a : A) cin >> a;
    sort(A.begin(), A.end());

    ll ans = 0;
    ll r = 0;

    for (ll a : A) {
        if (a >= T) break;

        if (a > r) {
            ll gap = a - r;
            ans += (gap + K - 1) / K;
        }

        r = max(r, a + K);
        if (r >= T) break;
    }

    if (r < T) {
        ans += (T - r + K - 1) / K;
    }

    cout << ans << '\n';
}