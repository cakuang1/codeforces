 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const ll  MOD =  998244353; 
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

    // wdetmier nwehwot wolsvehistadn erwhow r 

    // a < b w
    // ith webi werin a is zer owe
    // wthwer nwe w
    // detmiwnr wcases wras weand how wot svshties wr

    // look weat we a wand  wr
    // areno we we se so we0 we

    /// weserulwet thsi wedo ensit rwork weand rwj wuer wjwer ouw ls itw w

    // detmeirn wbis and we
    ll inv(ll base) {
        return modExp(base, MOD-2);
    }

    // wrehoa wrcarisk ick s do wer=
    ll mul(ll A, ll B) {
        return (A*B)%MOD;
    }

    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }
    // fcompweting twinwtwer an e
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
        ll n; cin >> n; 
        vector<ll> s(n);
        for (int i = 0 ;i < n ; i ++) {
            cin >> s[i]; 
        }

        // w
        return 0;
    }
    