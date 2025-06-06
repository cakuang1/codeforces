

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



#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 3005;

int dp[MAXN][MAXN];
int prefix[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    string s;
    cin >> N >> s;
    for (int j = 1; j <= N; j++) {
        dp[1][j] = 1;
    }

    
    for (int i = 2; i <= N; i++) {
        // Compute prefix sums for dp[i-1][j]
        prefix[i-1][0] = 0;
        for (int j = 1; j <= N; j++) {
            prefix[i-1][j] = (prefix[i-1][j-1] + dp[i-1][j]) % MOD;
        }

        // Transition
        for (int j = 1; j <= i; j++) {
            if (s[i-2] == '<') {
                dp[i][j] = prefix[i-1][j-1]; // Sum of all dp[i-1][k] where k < j
            } else { // s[i-2] == '>'
                dp[i][j] = (prefix[i-1][i-1] - prefix[i-1][j-1] + MOD) % MOD; // Sum of all dp[i-1][k] where k > j
            }
        }
    }

    // Compute the result
    int result = 0;
    for (int j = 1; j <= N; j++) {
        result = (result + dp[N][j]) % MOD;
    }

    cout << result << endl;
    return 0;
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    ll n ; cin >> n; 
    string s; cin >> s;



    // how many numbers remaining wreatet htna we
    
        
  	return 0;
}
 

