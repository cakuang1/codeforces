

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




struct query
{
    int index;
    int a; 
    int b; 
    int e;
    string res; 

};

int MAXN = 200005; 
int parent[MAXN];
int find(int a) {
    if (parent[a] == a) return a; 
    return parent[a] = find(parent[a]);
}
void unite(int a ,int b) {
     int pa = find(a);
     int pb  = find(b);
     if (pb == pa) continue ;
     parent[pa] = pb;
}

void solve() {
    int n,m; cin >> n >> m;  
    vector<int> heights(n + 1);
    for (int i=  1 ; i <=n ; i ++) cin >> heights[i]; 
    vector<vector<int >> adj ;
    for (int i = 0 ; i < m;  i ++) {
        int a ,b;
        cin >> a >> b; 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int q; cin >> q; 
    vector<query>  queries(q) ; 
    for (int i = 0 ; i  < q; i ++ ) {
        cin >> queries[i].a >> queries[i].b >> queries[i].c;
        queries[i].index = i;         
    }

     
    for (int i = 0 ; i < q ; i ++) {

    }    
        
    }

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    
    

  	return 0;
}
 

