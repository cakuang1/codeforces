#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD2 = 998244353;
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001;

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
    for (int i = 1; i < MX; i++) {  // FIXED LOOP
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // FIXED DP DECLARATION
    vector<ll> dp(n, INF);
    
    // Base cases
    dp[0] = 0;
    if (n > 1) dp[1] = abs(arr[1] - arr[0]);

    // DP Transition
    for (int i = 2; i < n; i++) {
        dp[i] = min(dp[i - 1] + abs(arr[i] - arr[i - 1]), 
                    dp[i - 2] + abs(arr[i] - arr[i - 2]));  // FIXED VARIABLE NAME
    }

    cout << dp[n - 1] << endl;

    return 0;
}