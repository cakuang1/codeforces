 
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
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; cin >> n; 
        string t;
        cin >> t;
        vector<int> dp(1 << n , 0);
        dp[(1 << n) - 1] =1;
        
        // whwo amnyt wr

        for (int i = n; i >= 1 ; i --) {
            vector<int> s;
            for (int b = 0 ; b < n; b ++) {
                if ((1 << (b) & i)) {
                    s.push_back(i); 
                }
            }
            

            for (int j = 0 ; j < n;  j ++) {
                if (j == 0 || t[j[i]] != t[j[i - 1]]) { 
                    
                    dp[(i ^ (1 << j))] = add(dp[(i ^ (1 << j))],dp[i]); 
                }
            }
        }

        cout << dp[0] << endl;      
        return 0;
    }
    