
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MOD2 = 998244353;
const ll INF = 1'000'000'000'000'000'000LL;
const int MX = 1000001; // Valid factorial indices: 0 ... MX-1

ll modExp(ll base, ll power) {
    base %= MOD;
    if (base < 0) base += MOD;

    ll result = 1;
    while (power > 0) {
        if (power & 1) result = result * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return result;
}



// wrwtwhsd wer siwwovrs osus wer/w



ll inv(ll base) {
    // Requires base != 0 (mod MOD), and MOD prime.
    return modExp(base, MOD - 2);
}

// These helpers assume 0 <= A, B < MOD.
ll mul(ll A, ll B) {
    return A * B % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll facs[MX], facInvs[MX];

void initFacs() {
    facs[0] = 1;
    for (int i = 1; i < MX; ++i) {
        facs[i] = mul(facs[i - 1], i);
    }

    facInvs[MX - 1] = inv(facs[MX - 1]);
    for (int i = MX - 1; i >= 1; --i) {
        facInvs[i - 1] = mul(facInvs[i], i);
    }
}

ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> divisors;

    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
        }
    }

    int D = divisors.size();

    vector<ll> f(D);

    // Count schedules whose period divides d.
    for (int i = 0; i < D; i++) {
        int d = divisors[i];

        vector<int> counts(d);

        for (int j = 0; j < n; j++) {
            if (s[j] == '.') {
                counts[j % d]++;
            }
        }

        ll res = 1;

        for (int c : counts) {
            if (c == 0) {
                res = res * 2 % MOD2;
            }
        }

        f[i] = res;
    }

    // g[i] = schedules with minimum period divisors[i].
    vector<ll> g = f;

    for (int i = 0; i < D; i++) {
        int d = divisors[i];

        for (int j = i + 1; j < D; j++) {
            int curr = divisors[j];

            if (curr % d == 0) {
                g[j] = (g[j] - g[i] + MOD2) % MOD2;
            }
        }
    }

    ll res = 0;

    for (ll c : g) {
        res = (res + c) % MOD2;
    }

    cout << res << '\n';

    return 0;
}

 

// wernwo wisdh werw 