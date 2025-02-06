

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


int dp[1 << 16][17][17];


int cost1(vector<int> s1, vector<int> s2) {
    int m = 2e9;
    for (int i = 0 ;  i < s1.size() ; i ++) {
        m = min(m, abs(s1[i] - s2[i])); 
    }
    return m;
}
int cost2(vector<int> s1, vector<int> s2) {
    int m = 1e9;
    for (int i = 1;  i < s1.size() ; i ++) {
        m = min(m, abs(s1[i] - s2[i - 1])); 
    }
    return m;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    int n ,m ; cin >> n >>m;
    vector<vector<int>> matrix(n, vector<int> (m));
    for (int i = 0 ; i < n; i ++) {
        for (int j = 0 ; j < m ;j ++) {
            cin >> matrix[i][j];
        }
    }
        if (n == 1) {
            int test = 1e9; 
            for (int i = 1; i < m; i++) {
                test  = min(abs(matrix[0][i] - matrix[0][i - 1]), test);
            }  
            cout << test << endl;
            return 0 ;
        }
    vector<vector<int>> dist1(n, vector<int> (n));
    vector<vector<int>> dist2(n, vector<int> (n));
    for (int i = 0 ; i < n; i ++) {
        for (int j = 0 ; j < n; j ++) {
            dist1[i][j] =  cost1(matrix[i], matrix[j]); 
            dist2[i][j] =  cost2(matrix[i], matrix[j]); 
        }
    }
    memset(dp,0, sizeof(dp)); 
    for (int i = 0 ; i < n  ; i ++) {
        int bm = 1 << i;  
        dp[bm][i][i] = 2e9;
    }
    for (int i = 0 ; i < (1 << n) - 1 ; i ++) {
        for (int j = 0 ; j < n ; j ++) {
            for (int k = 0 ; k < n ; k ++) {    
                int count = __builtin_popcountll(i); 
                if (count == 1 || j != k) {
                    if ( (i & (1 << j)) && (i & (1 << k)) )  {
                        for (int newbit = 0 ; newbit < n; newbit ++) {
                            if (!((1 << newbit) & i)) {
                                int cost = min(dp[i][j][k],dist1[k][newbit]); 
                                int newbm = ((1 << newbit) | i); 
                                dp[newbm][j][newbit] = max(cost,dp[newbm][j][newbit]); 
                            }
                        }

                    }         
                }
                    
            }
        }
    }
    int res = 0; 
    for (int i = 0 ; i < n; i ++) {
        for (int j = 0 ; j < n ;j ++) {
            if (i == j) {
                continue;
            }
            res = max(res, min(dp[(1 << n) - 1][i][j], dist2[i][j])); 
        } 
    }
    cout << res << endl;
  	return 0;
}

// does tsh wreally 
 

