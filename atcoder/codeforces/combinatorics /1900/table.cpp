

#include <bits/stdc++.h>
 
using namespace std;

using ll = long long;
const int MOD2 =  998244353; 
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001; //check the limits, dummy




ll modExp(ll base, ll power) {
    if (power == 0) {
        return 1;
    } else {
        ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
        if (power % 2 == 1) cur = cur * base;
        cur = cur % MOD;
        return cur;
    }
}

ll inv(ll base) {
	return modExp(base, MOD-2);
}


ll mul(ll A, ll B) {
	return (A*B)%MOD;
}

ll addi(ll A, ll B) {
	return (A+B)%MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll sub(ll A, ll B) {
    return (A-B+MOD)%MOD;
}

ll* facs = new ll[MX];
ll* facInvs = new ll[MX];

ll choose(ll a, ll b) {
	if (b > a) return 0;
	if (a < 0) return 0;
	if (b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a-b]);
    return cur;
}

int NMAX =  101;


void initFacs() {
	facs[0] = 1;
	facInvs[0] = 1;
	for (int i = 1 ; i < NMAX  ; i ++ ) {
		facs[i] = (facs[i-1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}


// for each column determine the number of ways 
// try all possible values for this row 

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    initFacs(); 
    ll n ,m ,k; cin >> n >> m >> k;

    vector<vector<int>> dp(n + 1 ,vector<int> (k + 1, 0));
    dp[0][0] = 1; 
    vector<vector<ll>> dpExp(n, vector<ll>(n + 1, 0));
    ll baseCt = m / n;
    ll extra = m % n;
    for (int i = 0; i < n; i++) {
        ll ct = baseCt + (i < extra ? 1 : 0);
        for (int add = 0; add <= n; add++) {
            ll c = choose(n, add);
            dpExp[i][add] = modExp(c, ct);
        }
    }

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j <= k; j++) {
            if (dp[i][j] == 0) continue;
            for (int add = 0; add <= n; add++) {
                if (add + j > k) break;
                dp[i + 1][add + j] = addi(dp[i + 1][add + j], mul(dp[i][j], dpExp[i][add]));
            }
        }
    }
    cout << dp[n][k] << endl;
  	return 0;
}

// focus only on  wr
 

