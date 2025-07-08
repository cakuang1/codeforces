 
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

    struct Fw  {
        ll a,b ,t

        bool operator< (Fw const& o) {
            return t < o.t; 
        }
    }

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        ll n, m,d ; cin >> n >> m >> d; 
        
        vector<Fw> arr(m);
        for (int i = 0 ;i < m ; i++) {
            cin >> arr[i].a >> arr[i].b >> arr[i].d; 
        }

        sort(arr.begin(),arr.end()); 
        vector<ll> dp(n + 1);
        for (int i = 1 ; i <= n;  i++) {
            dp[i] = arr[0].b - (abs(arr[0].a  -  i));   
        }  
        
        
        for (int i = 1; i < m ; i ++ ) {
            int T = (arr[i].t - arr[i - 1].t)* d;
            vector<ll> newdp(n + 1);
            deque<int> dq; 
            for (int j = 1;  j <= n; j ++) {
                while(!dq.empty() && dq.front() < j - T)
                    dq.pop_front();
                // 2) maintain deque in decreasing dp_prev[] order
                while(!dq.empty() && dp_prev[dq.back()] <= dp_prev[j])
                    dq.pop_back();
                // 3) push this index
                dq.push_back(j); 

                newdp[j] = max(newdp); 
            }

            for (int j = n; j >= 1;  j --) {

            }

            swap(dp,newdp);
            
        }

        ll res = *max_element(dp.begin(), dp.end());

        cout << res << endl;
    
        return 0;
    }
    