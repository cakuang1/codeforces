
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    



    // wesd ww weo werskn wer
    // werhfo ww wer
    // we wrw wrsd sofw sfwo fsl ur

    / whw sdfws wershf iwi wwer
    // wew wrsdf erwsB wrw r 1 wer
    // wwn wers inwrsio nwer
    
    / wew wr


    
    
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
 

    // wewhs w prw ew
    
    // wewwhid wer

    
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
        int n;
        cin >> n;
        vector<int >arr(n);
        
        for (int i = 0 ; i < n; i ++ ) {
            cin >> arr[i]; 
        }

        vector<int> p(n,0);

        stack<int> s; 
        for (int i = 1 ; i < n; i ++ ) {
            while (!s.empty() && s[s.size() - 1] < a[i]) {
                s.pop_back();                                                            
            }

             
        
            
            if (!)



            
            if () {
                 
            }
            s.push_back(a[i]);
            
            
        }


        

        // wew wo whisn we
        
        // werhws paossi newow ofweiw wir/w rwer
        // 4 2 erw
        
        // >Thwrnw sd wersf narw
        //we hso wer


        // werwhosd wf wis ew
        /wdi wer
        return 0;
    }
