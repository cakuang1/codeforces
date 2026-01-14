#include <bits/stdc++.h>
 
using namespace std;

using ll = long long;
const int MOD =  998244353; 
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
	for (int i = 1 ; i < 30  ; i ++ ) {
		facs[i] = (facs[i-1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}



int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    initFacs(); 
    int n ,m ; cin >> n >> m; 
    vector<vector<int>> counts(m + 1, vector<int> (n + 2, 0 )); 
    for (int i = 1 ; i <=  n ; i ++) {
        for (int j = 1 ; j <=  m ; j ++) {
            int distance; cin >> distance; 
            counts[j][distance] ++;          
        }        
    } 
    ll res = 0;
    for (int currm = 1 ; currm <= m ; currm ++)  {
        ll count = counts[currm][n + 1]; 
        ll total = count;
        ll chosen = 0;
        for (int i = n ; i >= 1;  i --) {
            total += counts[currm][i];
            count = mul(count, total - (chosen));
            chosen ++; 
        }
        ll addi = sub(1, count * facInvs[n]);
        res = add(res, addi); 
    }

    cout << res << endl;
    

    
  	return 0;
}
 

