#include <bits/stdc++.h>
using namespace std;

using ll = long long;



// where wrhew eoul ouw erhad w



// wis c osertsf we


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<ll> c(N);
        for (ll &x : c) cin >> x;

        sort(c.begin(), c.end());

        vector<ll> pref(N + 1);
        for (int i = 0; i < N; i++) {
            pref[i + 1] = pref[i] + c[i];
        }

        int V = N - 1;           // c[N-1] is the isolated vertex
        ll ans = (1LL << 62);

        for (int k = 1; k <= V; k++) {
            ll cur = pref[V] + pref[k];

            if (V >= 3 * k) {
                cur += 1LL * (V - 3 * k) * c[0];
            } else {
                cur += 1LL * ((V - k) % 2) * c[0];
            }

            ans = min(ans, cur);
        }

        cout << ans << '\n';
    }
}