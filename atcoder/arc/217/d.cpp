
// erin dsrsithsi wr


// w rsdfhsif wr sc sfwfw
//w r sfisncs sgsersd fwtnw wvrs x sf 
// we


//// wrw hso sofso wrw
// we w

// wrisdntseh sujm wermod fsursl r
//; weem
// wr
// wrwsithes nsf mewr
// all wersdinsct wnubmsersdf sec spresr
// we whosossfssoeri
// wesdosetsf wrw
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


    // wwt fww spwp scan fosethis
    // wcoser swo nwer
    // wercsor sfwrhwi
    // weho iis rowfsfs dt dsitoht
    // wew fs sfoprsi hrwr
    // ww hsofsrw
    //wers nsos sfsons svsf c angew

    // wrasf sofsprao sersih
    

    // interrior apths wecna be wer
    void solve() { 
        int n;
        cin >> n; 
        int k ; cin >> k;

    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t;
        while (t --) {
            solve(); 
        }
        return 0;
    }
    
    // ww wnubmr wabd rsipsfw sby countw isths co msprsler
    
    // splits 
    // wewwusj wr sf kwra hos swer
    
     
    // ww sdtshosiwrwrw
    / wrshfowr
    // wsftmwi sfs wrosd fwerw//w  ws ses change
    // ww ssgn f er

    // wrwsvss oins fbacsd ser
    /// ws rsd suer