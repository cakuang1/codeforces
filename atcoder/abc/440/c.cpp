 
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
    // w
    

    void solve() { 
        int n,w;
        cin >> n >> w;
        vector<int> arr(n);
        for (int i = 0 ;i < n; i ++ ) {
            cin >> arr[i]; 
        }
        

        // this wrmakseset sences wrin a circlew r

        // ww hatdsoshtoso werw rewprsrsetsint? w
        // wecearis testsfowthat ehsi twer
        //wrs dish siwirwoemr wer       
        int s = 0; 

        vector<int> pref(n);  

            for (int i = 0 ;i < n ; i ++) {
        
        }
        
        // add one to x until y ouwew wersdf r e sishtsidf wr w
        // D osehtso werkw
        // w
        /
        // clrealy wry eyou wetwe yewouvmose sforearsd werowne
        // Esdosthiwowrow wkr
        //wew hh WEOr dogusetshidof werw
        // weW hsydtsoeshti ser
        // sliding wewind owerof weisze we
        
        // start with x = 0;
        

        // gaps erwiths ershf wewf hsdogbosusod hiaon werhsd ts
        // sliding wrwind owetwe of wris z rwew
        // wDFosts woerm aketss ner w
        // we HERO wdosetsvhsotih s
        // Wh sdytso wirwot wk
        / wx
    } 

    // wewrsyw oeucnasfhistswetims lstisnf we 
    // What aabou tthse stimeslf iesnts
    // Wr hsdytsdp owthwi sdwerowk w

    // Wh syetsd hsos woej woer
    int main()  {

        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t; 
        while (t --) {
            solve(); 
        }
        return 0;
    }


