w

#include <bits/stdc++.h>
 
using namespace std;

using ll = long long;
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





int dp[1001][1001];




// dp[i][j] = sum of all possible rectangles within n,m 





// think of the rectangle starting from the topleft 


// potential  (n - 2 ) * (m - 2) starting points 

// if you start at tw  what does thsi wemean we


// potential endpoints and how to solve this wer
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    int n , m , k ; cin >> n >> k ;
    for (int i = 0 ; i < 1001; i ++) {
        for ( int  j = 0 ; j < 1001 ; j ++) {
            dp[i][j] = 0 ; 
         } 
    }        

    // why does this work 


  	return 0;
}
 

