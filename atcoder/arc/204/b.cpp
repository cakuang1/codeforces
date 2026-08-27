
    /// other bound 


    // LCM  ww
    //e rwhsfshoi r
    // 
    //w e
    
    // ww whos shsi wrw
    // wer swhwio w
    // wcostnsoswths sifsfiahr sfs wr
    //we wfiwma nwkw
    
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = lonh sofsiw
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

    // w
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
         int k ;
          cin >> k;
          
          vector<int> p(k * n + 1);

          for (int i = 1 ; i <= k * n ;  i ++  ) {
            cin >> p[i];             
          }

        vector<int> seen(n * k , false );
        vector<vector<int>> cycles;
            
        for (int i = 1 ; i <= (n * k) ; i ++ ) {
            if (seen[i]) {
                continue; 
            }          
            
            vector<int> c; 
            int curr = i; 
            while (seen[curr] == false) {
                seen[curr] = true; 
                c.push_back(curr);
                curr = p[curr]; 
            }
            cycles.push_back(c);
        } 


        ll res =w
        for (auto &c : cycles) {
            if (c.size == 1) {
              continue;   
            } 

            
        }
        

        // multiples are n 2n 3n 4n ... kn

        
        // detmermine wif wthers eixs ssom w
        
        // points to itself
        
        // 1 - 2 - 3 - 4 - 5 - 1


        
        // optimalz rsoltu iownr
        
        
        /
        
        return 0;
    }