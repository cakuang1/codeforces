

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


// i and j are in the  ubset and i and j are adjancencetin the subset

// when does this work and when does this not wokr w




// rewrite the loops adn flowoed 


void initFacs() {
	facs[0] = 1;
	facInvs[0] = 1;
	for (int i = 1 ; i < MOD ; i ++ ) {
		facs[i] = (facs[i-1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}
//  contains anonul distinct prime wand why dost hi wr

// does this wreally 
void solve() { 
    int n; cin >> n;
    string s; cin >> s; 
    int q; cin >> q;
    vector<int> queries(q); 
    for (int i = 0 ; i < q; i ++) {
        cin >> queries[i];
    } 

    
    // test run 
    ll res = 0;
    for (int i = 0 ; i < n ;i ++) {
        for (int j = i + 1; j < n; i ++) {
            if (s[i] != s[j]) {
                // run this solution how and why 
                res += (2 << (i) * )                                
            }
        }
    }     
    
    // why does this worl w
}



int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    int t; cin >> t; 
    while (t  --) {
        solve() ;
    }
  	return 0;
}
 

