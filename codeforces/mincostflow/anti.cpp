 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    // the ahrdserset parwt si reduceisng thsi wewy w wer
    // w
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
        int n; cin >> n;
        string s; cin >> s;
        
        vector<int> arr(n);
        for (int i =0 ; i < n; i++) {
            cin >> arr[i];     
        }

        return 0;
    }



    // wantwi erspaldonser womic wer
    // you wrcanan to maximumwe rteh buery erof the array w

    // w 

    // wsyntrwrmatricse we
    // wdetmeir nwewhat w they wecan be weadn wew what we
    //vefert pari uses two distinct letters we
    // w w
    // one node wefor eacvh weapri we
    // wdetmiern wew w
    
    // detmienr weeach weapir werw

    // rholy shitw rwahtw ew