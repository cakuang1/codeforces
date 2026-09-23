
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



    // wes fsh s wriw
    ll choose(ll a, ll b) {
        if (b > a) return 0;
        if (a < 0) return 0;
        if (b < 0) return 0;
        ll cur = facs[a];
        cur = mul(cur, facInvs[b]);
        cur = mul(cur, facInvs[a-b]);
        return cur;
    }
     
    // wrwwhrsd ssf isrso sdgbe O rw e

    // w wsd w sm o fs wlerw

    // ww swo
    // wwhat ssfns wrw w still ahves nsot ssfusn wthat fina lb it bv sos e 1 w
    // wernwd  = 1 wm; w

    // w
    // wersdosfs wr 
    // yo uweads sesdf rnwsd eing 
    
    // yo wurw s wes sonlys rf wersd wer
    
    // werw m Ifs swhsdf wer weros ssd ewrw wls Kwer w
    void initFacs() {

        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }




    // werwh osfwhds wersf i fweros a wrwer
    // wer wfsd wp wrms mwsd. whtw ewr
    
    void solve() { 
    
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t;
        cin >> t;
        while (t --) {
            solve(); 
        }
        return 0;
    }
