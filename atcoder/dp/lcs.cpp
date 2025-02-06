

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



int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    

    string s1, s2; cin >> s1 >> s2;
    int n1 = s1.length();
    int n2 = s2.length(); 
    vector<vector<int>> dp(n1 + 1 ,vector<int> (n2 + 1 , 0 )); 


    for (int i = 1 ; i <= n1 ; i ++) {
        for (int j = 1 ; j <= n2 ; j ++) {
            if (s1[i - 1] ==  s2[j - 1]) {
                dp[i][j]  = dp[i - 1][j - 1] + 1;                
            }else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); 
            }   
        }
    } 


    int i = n1;
    int j = n2; 

    string res = ""; 
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            res += s1[i - 1]; 
            i --;
            j --;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i --;
        } else {
            j --; 
        }
    }    


    reverse(res.begin(), res.end()); 
    cout << res << endl;
    
  	return 0;
}
 

