 
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

    // weoertis sfsd wer
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
         ll n; cin >> n; 

         // fix some y
         // determine the interval if floor roots for this y 

         // detemrine  

         // 1 [1,3];

         // 2 [4,8];


         // 3 [9,15];
        

         // 4 [16,24];


         // 5 [25 , 35];


         // rwh owmans poseitna fanrges dothere
         
         // wwhoamy nweososbils lvaues are uo sitns aitnsg w
         / we


         // 10^18 
         ///hwo mantw erpsosbiwler. avlauew 
         
         // still ert wedsfiscu lwtwe 
         
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



    // wets sdfa er
    // repsixf fsi whroso sfsl ihwr./ we

    // 1 
    
    // 1 2 3
    // 2  
    // 4 5 6  7 8 

    // 3
    // 9 .. 15

    //
    // wrho sosmsiudfsraseithere
      w
    // wtwhewn arhw
    // wrhsodf hwiero