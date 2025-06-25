#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while (T--) {
        int n, k;
        ll d;
        cin >> n >> k >> d;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> v(k);
        for (int i = 0; i < k; i++) cin >> v[i];

        // window for first reset: t in [1..L], but also t=1 reset-before-add
        ll L = min(d, (ll)2*n);

        // 1) consider resetting immediately on day 1 (no adds yet)
        ll best = 0;
        {
            ll c0 = 0;
            for (int j = 0; j < n; j++)
                if (a[j] == j+1) c0++;
            // days left = d-1
            ll extra0 = (d - 1) / 2;
            best = c0 + extra0;
        }

        // 2) simulate with prefix-adds, resetting on day t AFTER the add
        vector<int> cnt(n, 0);
        for (ll t = 1; t <= L; t++) {
            // do the add of day t
            int b = v[(t-1) % k];
            for (int j = 0; j < b; j++)
                cnt[j]++;

            // now reset on day t
            ll c1 = 0;
            for (int j = 0; j < n; j++)
                if (a[j] + cnt[j] == j+1)
                    c1++;

            // days remaining = d - t
            ll extra = (d - t) / 2;
            best = max(best, c1 + extra);
        }

        cout << best << "\n";
    }
    return 0;
}
