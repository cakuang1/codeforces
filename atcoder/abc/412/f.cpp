 
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


    // wbook wereueist =werthe hriwline conatins wen intesgser er
    // wwths wrsi wsafl werw quseiton wwww qcoorecwet er
    // we
    // wfwe wer 
    // chososewa set wrw  w w wedo sethi wrworkw radn erwh owd oyou dsotu osovlsehtis d nwewr ehwyd sowtis erwiwtwer
    // weits wer
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
        ll  n; cin >> n; 
        ll c;  cin >> c;
        c --;
        ll s = 0;
        vector<pair<ll,ll>> arr(n); 
        for (int i = 0 ; i < n; i ++) {
            cin >> arr[i].first;
            arr[i].second = i; 
            s +=  w
        }


        // wet akts thsi gni twus mwew
        ll  count = arr[c]; 
        sort(arr.begin(),arr.end()); 
        
        reverse(arr.begin(),arr.end()); 
        vector<ll> dp(n,INF); 

        ll leftsum = 0;
        ll rightsum  = 0;
         
        for (int i = 0 ;i < n; i ++ ){
            rightsum = add(rightsum,dvd(arr[i].first,s - 1)); 
        }
        for (int i = 0 ; i < n; i ++ ) { 
            rightsum = sub(rightsum , arr[i].first , s - 1); 
            
            ll nume = add(1,leftsum);
            ll den = sub(1,rightsum);
            dp[i] = dvd(nume,den);
            
            ll newadd = dvd(add(arr[i].first, dp[i]), s - 1); 
            leftsum = add(leftsum,); 
        }
        
        cout << dp[c] << endl; 
        return 0; 


    }


