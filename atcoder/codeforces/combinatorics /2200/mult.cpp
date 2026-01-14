

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

ll add(ll A, ll B) {
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



void initFacs() {
	facs[0] = 1;
	facInvs[0] = 1;
	for (int i = 1 ; i < MOD ; i ++ ) {
		facs[i] = (facs[i-1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}


vector<ll> getDivisors(int x) {
    vector<ll> divisors;
    // Check divisors from 2 up to sqrt(x)
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            divisors.push_back(i);
            if (i != x / i)
                divisors.push_back(x / i);
        }
    }
    // x itself is also a divisor (if x > 1)
    if (x > 1)
        divisors.push_back(x);
    return divisors;
}




int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    int t ; cin >> t;

    vector<vector<ll>> dp(100001, vector<ll> (17));
    for (int i = 2 ; i <= 100000 ; i ++) {
        dp[1][i] = 1;
    }

    
    for (int i = 2 ;  i <= 100000 ; i ++) {

        vector<
        dp[] ;
    }
    while (t -- ) {
        int k, n; cin >> k >> n;
        
    }

    /w    
  	return 0;
}
 

