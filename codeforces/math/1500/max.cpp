 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e13;
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


    ll kadane(const vector<ll>& a) {
        ll best = a[0];
        ll current = a[0];
        int n = (int)a.size();
        for (int i = 1; i < n; i++) {
            // Either extend the previous subarray, or start fresh at a[i]:
            current = max(a[i], current + a[i]);
            best = max(best, current);
        }
        return best;
    }
    

    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t ; cin >> t;
        while (t -- ) {
            ll  n ; cin >> n;
            ll k ; cin >> k;
            string s; cin >> s; 
            vector<int> arr(n);
            for (int i = 0 ; i< n; i ++) {
                cin >> arr[i]; 
            } 
            int count = 0; 
            for (char c :s) {
                if (c == '1') {
                    count ++;    
                }
            }
        
            if (count == n) {
                if (kadane(arr) == k) {
                    cout << "YES" << endl;
                    for (int i = 0 ; i < n; i ++) {
                        cout <<  arr[i] << " ";
                    }
                } else { 
                    cout << "NO" << endl; 
                } 
                
            } else {
                
            }
            
            // first check using kadanes 
        }        
        return 0;
    }
    