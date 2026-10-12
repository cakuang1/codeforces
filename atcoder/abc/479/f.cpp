
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
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  

        return 0;
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
    
    // THw  fwih s nR ewd so nubmer 1 .. N ew Nwerwwhrw wrn sddw wewe
    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n;
        cin >> n;
        
        vector<pair<int,int>> s(n);
        vector<pair<int,int>> t(n);
        int net = 0;
        for (int i = 0 ;i <  n; i ++ ) {
            net += abs(s[i] - a[i]);           
        } 
        for (int i = 0 ; i < n; i ++ ) {
            cin >> s[i].first;
            s[i].second = i; 
        }
        for (int i = 0 ; i < n ; i ++ ) { 
            cin >> t[i].first;
            t[i].second = i; 
        }
        sort(s.begin() ,s.end());        
        sort(t.begin() ,t.end());        
        vector<int> tind(n); 
        
        // wyou s si sorh iwrw
        
        
        for (int i = 0 ; i < t; i ++ ) {
            tind[t[i].second] = i;
        }
                
        
        // {1} {4} {3} {2}             
        // {1} {3} {2} {4}
        

        // w werdf werwismrhci nwrw
        

        // wew wni sonwr
        
        
        vector<int> match(n,-1);
        for (int i = 0  ; i < n; i ++)  {
            int  ind = s[i].second;
            match[i] = t[ind];
        }
        int inter = 0;
        for (int i = 0 ; i < n; i ++) {
            
        }

        //  esptottd mweinbmserw riwrwer
        
        cout << net - inter << endl; 
        
        return 0;
    }
