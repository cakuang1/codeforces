 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
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
     
    bool isPalin[501][501];
    int dp [501][501];
    
    int  solve(int l , int r) {
        if (isPalin[l][r]) {
            return 1;
        }  
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        int res = 1e9;
        for (int i = l ; i < r ; i ++) {
            res =  min(res, dp[l][i] + dp[i + 1][r]); 
        }
        return dp[i][j] = res;
    }
    
    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int  n; cin >> n; 
        vector<int> arr(n);
        for (int i = 0 ;i < n; i ++) {
            cin >> arr[i]; 
        }
        for (int i = n - 1 ; i >= 0 ; i -- ) {
            for (int j = i ; j < n  ; j ++  ) { 
                if (i == j) {
                    isPalin[i][j] = true;
                } else if (j - i == 1) {
                    if (arr[i] == [arr[j]]) { 
                        isPalin[i][j] = true;
                    }
                } else {
                    if (arr[i] == arr[j] && (isPalin[i + 1][j - 1])) {
                        isPalin[i][j] = true; 
                    }
                }
            }
        } 
        memset(dp,-1, sizeof(dp)); 
        cout << solve(0,n - 1) << endl;
        return 0;
    }
    