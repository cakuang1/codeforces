

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
ll dp[100005][11][3];
ll  n,m,k,x ; 

// dp[curr][count][ ]
void dfs(ll curr , ll parent, vector<vector<ll>> &adj) {
    
    int flag = 0;
    // solve for subtrees 
    for (ll child : adj[curr] ) { 
        if (child == parent) continue; 
        dfs(child, parent, adj);
        flag = 1; 
    }
    // base case

    // 1 2 3 4 5 
    if (!flag) {
        dp[curr][0][0] =  k - 1;
        dp[curr][1][1] = 1; 
        dp[curr][0][2] = m - k;
        return;
    }
    vector<vector<int> dp2(3,vector<int> (n + 1));
    dp2[1][0] = 1;
    dp2[2][0] = 1;
    dp2[3][0] = 1;
    // does this work  
    vector<vector<int> newdp2(3, vector<int> (n + 1));
    for (ll child : adj[curr]) {
        if (child == parent) continue;

        // take i from this subtree 
        for (int i = 0 ; i <= x ;  i ++) {
            int state0 = dp2[child][i][0];
            int state1 = dp2[child][i][1];
            int state2  = dp2[child][i][2];
            for (int j = i  ; j <= x ; j ++ ) { 
                newdp[0][j] = add(newdp[0][j], (state0 ) % MOD;
                // define dp[0][i] = can contain nodes from section 0 ,1 ,2;
                // define dp[1][i] = can only contain nodes from section 0                 
                // define dp[2][i] = can only contain nodes from section 0 and 2;

            }
        }
        swap(dp2 , newdp2);
    }    


    for (int i = )
}




int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    cin >> n >> m;
    vector<vector<ll>> adj(n + 1);
    for (int i = 0 ; i < n - 1 ;i ++) {
        ll a, b ;
        cin >> a >> b; 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }    
    cin >> k >> x; 


    dfs(1,- 1, adj);
    ll res = 0; 

    for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j <= k ; j ++) {
        res = add(res, dp[1][j][i]);
        }
    }
    cout << res << endl;
  	return 0;
}
 

