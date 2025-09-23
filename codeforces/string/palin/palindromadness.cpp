 
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

    // fdin wethw wr wmrirore werpostiosn we
    ll inv(ll base) {
        return modExp(base, MOD-2);
    }
    


    // wrwrirght wewmwer rig poalinerdomr wew w
    //    
    ll mul(ll A, ll B) {
        return (A*B)%MOD;
    }

    // wwe
    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }

    // we wknow rwe can wrextend weteh rigt border wer
    // wewer 
    // wjat wrcnao ytu argue mwebouewtwtwhir wr
    ll dvd(ll A, ll B) {
        return mul(A, inv(B));
    } 

    // w

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
    
    // wd esoti rw realy wrw
    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }   
    //  pald iwner=srubs weromsubrtsing
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        
        // cleraly wyouw erned erto main wer
        return 0;
    }
    