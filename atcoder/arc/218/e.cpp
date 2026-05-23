
#include <bits/stdc++.h>



// /weeww sdfnsspfsso cuwrw sfosfsififsdf sfsfs
// wrwf ofOfs fshfsof wer
// w dsfwisdf sfhwir
// wersdfdwofif wrw sdf sfa  fsfshfwo
// wr sdothwo wkr
// wer 
// wefwrsw werrwososfiwrw

// wrssi s sfs3 wer

//w cmserops sfsmsfis sfisngssiw
// absfd. sltus sseplxc svs eboug w wr




// wrw isfsos hwer




// we w sfwef sdof uwrw

// wr wrfhsousf wls fsr
/ 
// each wersndpsotsinf wrsh

// wechosoe wthsi wer
// we sfew sdfwnrw wishwirwrsdf iwer
// wchosie thfos her
//. dhosrs wersf w choose fso msher

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

    // equivilent sure
    
    // wesdsithsi wrw
    // werwsho rohi wer
    // wraosi so fsdfifsf si rw
    // wercnss sfs hisf. ws
    // wsohsifhs iows uwrso wer
    void  initFacs() {


        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n;
        cin >> n; 
        int q;  cin >> q;
        vector<int> arr(n);
        for (int i = 0 ; i < n; i ++ ) { 
            cin >> arr[i]; 
        } 
        

        for (int i = 0 ; i < q ; i ++) {
            ll x, k ; cin >> x >> k; 
                         
        }
        return 0;
    }   


    /// ww spltsi sinow 