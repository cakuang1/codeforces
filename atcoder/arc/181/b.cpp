    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    // wrhwrw shsi ssirs s fspsots snsion. fisdiwenrtsers// w

    // ww wssis is maksn s wnrw

    // ww ws sssfnsiw wr
    //w ewrwhs sfs smsfsms sofmsosmssls s f fs 2 wer// w
    // wr wh sfshs sd sewwl sos fss aobu tse obuarnsi wrw
    //tw owdsi sdnrs s fis nal s fsi s omsofpsfsf nsosn wir 
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

    // wrwe wfwersdf wr
    

    //

    // cowtuwssnsoet blco kwer
    // wrast s sss dg rsobwe f
    // wesfhsfssishs osk wrw
    //w anws isgs wr/ /we

    // s + s + t + 

    void solve() {
        string s; cin >> s;
        
        string x,y;
        cin >> x >> y;
        
    
    
        // 0 append S; 
        // 1 append T;
        int x0 = 0;
        int x1 = 0;
        int y0 = 0;
        int y1 = 0;
        
         
        for (char c : x) {
            if (c == '1') {
                x1 ++;                                 
            } else {
                x0 ++;
            }

            
        }

        

        for (char c : y) {
            if (c == 1) { 
                y1 ++;
            } else {
                y0 ++; 
            }
        }


        // w rq uislssnsisw
        // werhw wsf wrsfhis ns wri alsifnsw
        // This marsknskw r
        // wer= Sfsfsihisjf amsrnw
        // we wwno s ws hs. ow ksf
        //w 
        // wtwhtw nwe ws fhwowsof hsfosfh ohwirw
        // x0 * S + x1 * T = y0 * S + y1 * T; 
        
        

        // wrw sfihswsf sls sf erw
        // wr
    }

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  

        int t ; cin >> t;
        
        while (t -- ) {
            solve(); 
        } 
        return 0;
    }
