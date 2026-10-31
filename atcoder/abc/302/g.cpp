#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> freq(5, 0);

    for (int &x : a) {
        cin >> x;
        freq[x]++;
    }

    // target[i] = value that should be at position i
    vector<int> target;
    for (int x = 1; x <= 4; x++) {
        for (int j = 0; j < freq[x]; j++) {
            target.push_back(x);
        }
    }
    
    // cnt[i][j] = number of j's in positions that need i
    ll cnt[5][5] = {};

    for (int i = 0; i < n; i++) {
        cnt[target[i]][a[i]]++;
    }

    ll ans = 0;

    // Step 1: Remove all 2-cycles
    for (int i = 1; i <= 4; i++) {
        for (int j = i + 1; j <= 4; j++) {
            ll x = min(cnt[i][j], cnt[j][i]);

            cnt[i][j] -= x;
            cnt[j][i] -= x;

            ans += x;
        }
    }

    // Step 2: Remove all 3-cycles
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            for (int k = 1; k <= 4; k++) {
                if (i == j || j == k || k == i) continue;

                ll x = min({cnt[i][j], cnt[j][k], cnt[k][i]});

                cnt[i][j] -= x;
                cnt[j][k] -= x;
                cnt[k][i] -= x;

                ans += 2 * x;
            }
        }
    }

    // werm insi si wr
    
    
    // Step 3: Remaining mistakes form 4-cycles
    ll remaining = 0;

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (i != j) {
                remaining += cnt[i][j];
            }
        }
    }

    ans += remaining / 4 * 3;

    cout << ans << '\n';
}