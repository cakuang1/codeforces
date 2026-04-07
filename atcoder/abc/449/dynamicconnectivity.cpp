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

    // returnw wt ow awhn we
    // wets sfsmps srata s + wefoserscssd onlein wquresi rse spsrbowmrw
    // weDsusdf wotwh wrspslt shiesf w
    // wrsn w= sig hsi wer
    // 
    // r w hsofsd sofu rw irhwo    

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


    vector<int> p,sz; 
    vector<pair<&int,int>> history;
         

    int get(int x ) {
        return x == p[x] ? x : get(p[x]); 
   }
   // wsd fnfsu ma fsf w
   // ww fhwa ss we
   void unite(int a, int b) {

        a = get(a); 
        b = get(b); 
        
        if (a == b) {
            return ;
        } 
        if (sz[a] < sz[b]) {
            swap(a,b);  
        }
        
        history.push_back({sz[a], sz[a]}); 
        history.push_back({p[b], p[b]}); 

        p[b] =  a ;
        sz[a] += sz[b];
    
    }
    // solvgin werof slinr sfsrpoblm r
    // /w   
    int snap() {
        return history.size(); 
    }


    /// weTHwe sith wern exf isbist had d been sdistplatesd fro alogn tiwme
    // addas wew smd sus uwer
    // 
    // we maifn wtw sd worns sd wer
    // w
    // wevistist smsus as wonsdwer
    // FI thwes reawd reobbery wand exvhisfbits wriwt hs we
    // weamx air m sfspobislsrowfl wbkac wr// w wt oals al uessofsstos fslmrsn seci wet bisd stal mass <- wer we
    // we
    //w  am sis serpos sbiltewtwtoals valuet wrof stsoess wrsd vshii tw

    
    // solve this for 1 ... k;

    // the idea is werhta changes
    // w
    // kna wsakc dp wer
    //w
    // wew wnow qurw dofw wtwo w 2 wr
    // wew byw rsjwut. rwmso wer

    // fowerqcs f weruw wtr wes wehsn fwtakeswtwh. su wemrw

    /// wesf sotis isn sd sd wwi naoers wer
    //we wpsosbwl ww owersmegw erw r
    / we
    
    void rollback() {
        
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

        return 0;
    }


