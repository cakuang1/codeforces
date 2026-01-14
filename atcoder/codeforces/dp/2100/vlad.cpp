

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
        for (int i = 1 ; i < 1000 ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }

    




    int main() {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        initFacs();   
        int n,k ; cin >> n >> k; 
        vector<int> arr(n);
        for (int i = 0 ; i < n; i ++) {
            cin >> arr[i]; 
        }
        int maxblocks = n/k; 
        vector<vector<ll>> dp(n + 1, vector<ll> (maxblocks + 1));
        dp[0][0] = 1;   
        for (int i = 0 ;i < n ;i ++) {
            for (int block = 0 ; block <= maxblocks ; block ++) {
                if (block > 0) {                    
                    int size = 1; 
                    for (int k = i - 1 ; k >= 0 ; k -- ) {
                        if (arr[k] == arr[i]) {
                            size ++; 
                            if (size >= k) {
                                dp[i + 1][block] = add(dp[i][block] , dp[i - 1][block - 1] * choose(size - 2, k - 2)); 
                            }
                        }
                    } 
                    
                }        
                dp[i + 1][block] = add(dp[i + 1][block], dp[i][block]); 
            }            
        }
        for (int i = maxblocks ; i >= 0 ; i --) {
            if (dp[n][i] > 0) {
                cout << dp[n][i] << endl;
                return 0; 
            }
        }
        return 0;
    }





