#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll tmp = N;
    vector<pair<ll,int>> fac;
    int totalExp = 0;

    for (ll p = 2; p * p <= tmp; p++) {
        if (tmp % p == 0) {
            int e = 0;
            while (tmp % p == 0) {
                tmp /= p;
                e++;
            }
            fac.push_back({p, e});
            totalExp += e;
        }
    }
    if (tmp > 1) {
        fac.push_back({tmp, 1});
        totalExp++;
    }

    vector<ll> divs = {1};
    for (auto [p, e] : fac) {
        vector<ll> nd = divs;
        ll cur = 1;
        for (int i = 1; i <= e; i++) {
            cur *= p;
            for (ll d : divs) nd.push_back(d * cur);
        }
        divs = nd;
    }

    sort(divs.begin(), divs.end());

    int D = divs.size();
    unordered_map<ll,int> id;
    for (int i = 0; i < D; i++) id[divs[i]] = i;

    int K = totalExp + 1; // +1 because we may include 1

    vector<vector<ll>> cnt(D, vector<ll>(K + 1, 0));
    vector<vector<ll>> sum(D, vector<ll>(K + 1, 0));

    cnt[id[1]][0] = 1;

    for (ll x : divs) {
        auto ncnt = cnt;
        auto nsum = sum;

        for (int i = 0; i < D; i++) {
            ll p = divs[i];

            __int128 prod = (__int128)p * x;
            if (prod > N) continue;

            ll np = (ll)prod;
            if (N % np != 0) continue;

            int ni = id[np];

            for (int k = 0; k < K; k++) {
                if (cnt[i][k] == 0 && sum[i][k] == 0) continue;

                ncnt[ni][k + 1] += cnt[i][k];
                ncnt[ni][k + 1] %= MOD;

                nsum[ni][k + 1] += sum[i][k] + cnt[i][k] * (x % MOD);
                nsum[ni][k + 1] %= MOD;
            }
        }

        cnt = ncnt;
        sum = nsum;
    }

    vector<ll> fact(K + 1, 1);
    for (int i = 1; i <= K; i++) fact[i] = fact[i - 1] * i % MOD;

    int target = id[N];
    ll ans = 0;

    for (int k = 1; k <= K; k++) {
        ans += sum[target][k] * fact[k];
        ans %= MOD;
    }

    cout << ans << '\n';
}
// wrwhsfssfsf sts sfstihs ss weri