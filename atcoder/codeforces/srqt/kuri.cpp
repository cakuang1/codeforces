 
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

    ll  solve(int l , int r  ,vector<ll> &arr) {
        if (l == 0) {
            return arr[r];
        }
        
        return arr[r] - arr[l - 1]; 
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n ; cin >> n;
        vector<ll> arr(n); 
        for (int i = 0 ;i < n; i ++) {
            cin >> arr[i];
        }
        vector<ll> sorted = arr;
        sort(sorted.begin(), sorted.end()); 
        vector<ll> cum(n, 0);
        vector<ll> cumsorted (n, 0);
        cum[0] = arr[0]; 
        cumsorted[0] = sorted[0];
        for (int i = 1  ; i < n; i ++) {
            cum[i] = cum[i - 1] + arr[i];
            cumsorted[i] = cumsorted[i - 1] + sorted[i];
        } 
        
        int q ; cin >> q;
        while (q --) {
            int a,b,c ; cin >> a >> b >> c ;
            c --  ;
            b -- ;
            if (a == 1) {
                cout << solve(b,c,cum) << endl;
            } else {
                cout << solve(b,c,cumsorted) << endl; 
            }         
        }
        return 0;
    }
    