 
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

    void solve() {
        int n; cin >> n; 
        vector<int> arr(n);
        for (int i = 0 ; i < n; i ++ ) {
            cin >> arr[i]; 
        }
        vector<int> b(n,0);

        // look 
        
        
        // You want all to be one?
        
        
        // no deal with non detmerinatnsts
        // clearlyl wrwhats opstimal ? w
        
        
        // When is a position non determinant?

        
        // B[i] is non determinant if 

        // a[i] = -1 (No pointer)
        // or 
    
        // a[a[i]] = -1 (Pointer goes to  -1)

        // wesd bti pwerwkrn sd hwier sid nwersintssts ss ewinic wew
        // wer;lgkrng r n we


        // wedsstsi worow kdsersd hsogbouso sih wiw thwier ww
        // wGiwn w seom euncs er
        // w sn uwrkssehas dsescidns tocraeet ea new dsuewnusing this seuqenew
        // ww ds wrw ouvinfew omer sueqeinr ser of wlend n Each elsetmsi ner eiwtihw we

        // wrcinres eost msdks sti sersinreaing we
        // ds shtipw0rw osn w sihwo obuslts sfosithsi er
        // wdhs ysetosf hiwsd owrsk rwerm
        
        // er a yad stsh isrwowkr wa nrhwostus o ith
        // ww
        for (int i = 0 ; i < n; i ++) {
            if (a[i] != -1) {
                if (a[a[i]] != -1) {
                    b[i] = a[a[i]];
                }
            }
        }



        // wesd sd
        
        for (int i = 0 ;i < n; i ++ ){
            if (b[i] == 0) {
                                
                if (a[i] == -1) { 
                    
                }
            }        
        }
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t;

        while (t --) {
        
        }
        return 0;
    }


