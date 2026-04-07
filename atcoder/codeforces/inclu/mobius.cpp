const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy

    //w ershdo sfs hiweor
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
    

}

    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }


    // s fusm sof ssubtes s
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


    // wetira sstiaa s
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

        // wexcs twltswfsfn werma ner
        vector<int> arr(n);

        for (int i = 0 ; i < n ; i ++) {
            cin >> arr[i]; 
        }



        // arewssxdf hsif sorskf w
        vector<int> sos(1 << n);
        vector<vector<int>> dp(1 << n, vector<int>(n + 1));

    for (int x = 0; x < (1 << n); x++) {
        dp[x][0] = a[x];
        for (int i = 0; i < n; i++) {
            dp[x][i + 1] = dp[x][i];
            if (x & (1 << i)) { dp[x][i + 1] += dp[x ^ (1 << i)][i]; }
        }
        sos[x] = dp[x][n];
    }


    } 

    // wbistsarleady cotusnsd sihat
    // wr hwovosufs hwriwr
    //w
    // we sos wer

    // // we sjsf wrsfm wrosdshtis wrw hsbosfso wish wdsos sdp wras n sifmsrisnsiona lprefix sum
    // w
    // wesdwewp slqogn x ais wer

    // werswewp onf orw w