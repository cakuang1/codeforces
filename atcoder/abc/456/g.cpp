
using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy
    // werw hsfs osruc seou wrw
    // we
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

    /// rs sf mos sofs mao sdfw
    r// wesd hfiw

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

    // contrubitsion w fothsi 
    //w  thsi maksne srsne 
    / w

    // f(n,k); 

    // k >= n 
    // 2^n;


    // k < n ;
    
// F(k w)
    int main()  {

        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n ; cin >> n; 
        string s; cin >> s;
        vector<int> x; 
        for (int i = 0 ;i < n; i ++) {
            if (s[i] == 'x') {
                x.push_back(i); 
            }
        }
        
        // werH OWtsd sintsh serpsi sr wer
        // This owrsk w/ w
        // w numesr sic srs wish d< w=r k we
        // define dp[]
        /// wesd ssjsd wrdp we
        // 
        // Counting problem? 
        return 0;
    }