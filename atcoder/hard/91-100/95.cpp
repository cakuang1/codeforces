#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001; // Check the limits

ll modExp(ll base, ll power) {
    if (power == 0) return 1;
    ll cur = modExp(base, power / 2);
    cur = (cur * cur) % MOD;
    if (power % 2 == 1) cur = (cur * base) % MOD;
    return cur;
}

ll inv(ll base) {
    return modExp(base, MOD - 2);
}

ll mul(ll A, ll B) {
    return (A * B) % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

vector<ll> facs(MX), facInvs(MX);

ll choose(ll a, ll b) {
    if (b > a || a < 0 || b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a - b]);
    return cur;
}

void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MX; i++) {
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);    
    initFacs();

    int n, k; 
    cin >> n >> k;

    for (int i = 1; i <= k; i++) {
        ll gaps = n - k + 1;  
        ll bucketoptions = choose(gaps, i);  
        ll starsandbars = choose(k - 1, i - 1); // FIXED FORMULA

        ll result = mul(bucketoptions, starsandbars);
        cout << result << endl;  // FIXED OUTPUT FORMAT
    }

    return 0;
}
