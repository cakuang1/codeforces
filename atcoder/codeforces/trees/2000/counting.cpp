

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
	for (int i = 1 ; i < MOD ; i ++ ) {
		facs[i] = (facs[i-1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}


const int MAXN = 200000;
int p[MAXN+1],sz[MAXN+1];


int leader(int a ) {
    if (p[a] == a) return a;
    return p[a] = leader(p[a]); 
}

void unite(int a ,int b) {
    int pa = leader(a); 
    int pb = leader(b); 
    p[pa] = pb;
    sz[pb] += sz[pa]; 
}


void solve() {    
    ll n , s; cin >> n >> s; 
    for (int i = 1 ; i <= n; i ++) sz[i] = 1, p[i] = i;
    vector<tuple<ll,ll,ll>> edges;
    for (int i = 0 ; i < n-  1; i ++) {
        int a ,b, c ; cin >>  a >> b >> c;
        edges.push_back({c,a,b});
    }        
    sort(edges.begin(), edges.end());
    ll res = 1;
    for (int i = 0 ; i < n - 1; i ++) {
        auto [w,n1,n2] = edges[i]; 
        ll s1 = sz[leader(n1)];
        ll s2 = sz[leader(n2)];
        res = res * ( modExp(s - w + 1 , s1 * s2 - 1)) % MOD;
        unite(leader(n1) , leader(n2));
    }
    cout << res << endl;
} 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    

    int t ; cin >> t;
    while (t --) {
        solve();


                
    }
  	return 0;
}
 

