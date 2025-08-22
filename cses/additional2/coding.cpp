#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int M = 1e9 + 7;
const int K = 5e3;  // K is an offset to account for negatives

int main() {
	int n;
	int x;  // max penalty
	cin >> n >> x;
	vector<int> s(n);
	for (int i = 0; i < n; i++) { cin >> s[i]; }
	sort(s.begin(), s.end());

	/*
	 * dp[N][N][X] -> dp[i][j][k] = first i people, j unfinished groups, k
	 * penalty for convenience, we 1-index dp array and 0-index person array so
	 * dp[i][j][k] lines up with s[i] (i.e. skill of person i + 1 = s[i]) notice
	 * we only need to store 2 rows!
	 */

	// the subarray we're currently at
	vector<vector<ll>> dp1(n + 1, vector<ll>(x + K + 1));
	// the next subarray (we'll fill this up using dp1)
	vector<vector<ll>> dp2(n + 1, vector<ll>(x + K + 1));

	dp1[0][K] = 1;  // dp[0][0][0] -> 0 people, 0 unfinished groups, 0 penalty
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= (n - i); j++) {  // at most n - i unfinished groups
			for (int k = 0; k <= x + K; k++) {
				if (!dp1[j][k]) { continue; }
				dp2[j][k] += dp1[j][k];  // i has their own group
				if (j && k + s[i] <= x + K) {
					dp2[j - 1 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy



    // sqaur
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

    // does thi eweralmreally ermake any wesnsee wer
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
    ll cielDiv(ll A , ll B) {
        return (A + B - 1)/B;
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
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    // fdin the oconjecteinrue and thd oth eht
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        return 0;
    }
][k + s[i]] += j * dp1[j][k];  // finish group
				}
				if (j + 1 <= n - (i + 1)) {
					dp2[j + 1][k - s[i]] += dp1[j][k];  // create new unfinished group
				}
				if (j <= n - (i + 1)) {
					dp2[j][k] += j * dp1[j][k];  // extend unfinished group
				}
			}
		}
		for (int j = 0; j <= (n - (i + 1)); j++) {
			for (int k = 0; k <= x + K; k++) {
				dp1[j][k] = dp2[j][k] % M;  // i + 1 becomes the new i
				dp2[j][k] = 0;
			}
		}
	}

	int ans = 0;
	for (int i = K; i <= x + K; i++) {
		ans += dp1[0][i];
		ans %= M;
	}

	cout << ans << endl;
}