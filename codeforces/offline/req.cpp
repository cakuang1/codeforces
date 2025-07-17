 
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
    ll cielDiv(ll A , ll B) {
        return (A + B - 1)/B;
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
    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; cin >> n; 
        

        vector<int> arr(n);
        for (int i = 1 ; i <= n ; i ++) {
             cin >> arr[i]; 
        }
        int q;
         
        vector<int> res(q);
        vector<vector<pair<int,int>>> queries(n + 1); 
        for (int i = 0 ; i < q ; i ++ ) {
            int l,r; cin >> l >> r; 
            queries[r].push_back({l,i});      
        }
        
        map<int,int> lastprime;
    
        vector<int> prefix(n + 1, 1); 
        for (int i = 1  ; i <= i; i ++) {
             prefix[i] = mul(prefix[i - 1] , arr[i]);
        }

        int m =  ;  
        vector<int> contrib() 
        
        for (int i = 1; i <= n; i ++) {
        
        }
        
        for (int i = 0 ;i < q ; i ++) {
            cout << res[i] << endl; 
        }
        return 0;
    }
    
    const int MAXA = 1000000;
const int MOD  = 1000000007;

// fast exponentiation & modular inverse
ll modexp(ll b, ll e=MOD-2) {
    ll r=1;
    while(e){ if(e&1) r=r*b%MOD; b=b*b%MOD; e>>=1; }
    return r;
}

// Fenwick on multiplication
struct Fenwick {
    int n; vector<ll> f;
    Fenwick(int _n):n(_n),f(n+1,1){}
    // multiply f[i] *= v
    void update(int i, ll v){
        for(; i<=n; i+=i&-i) f[i]=f[i]*v%MOD;
    }
    // product over [1..i]
    ll query(int i){
        ll s=1;
        for(; i>0; i-=i&-i) s=s*f[i]%MOD;
        return s;
    }
    // product over [l..r]
    ll query(int l,int r){
        return query(r) * modexp(query(l-1)) % MOD;
    }
};

int spf[MAXA+1];
void build_spf(){
    for(int i=2;i<=MAXA;i++){
        if(!spf[i]){
            for(int j=i;j<=MAXA;j+=i)
                if(!spf[j]) spf[j]=i;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_spf();
    // precompute w_p = (p-1)*inv(p)%MOD
    vector<ll> wp(MAXA+1,1);
    for(int p=2;p<=MAXA;p++){
        if(spf[p]==p){
            wp[p] = (ll)(p-1) * modexp(p) % MOD;
        }
    }
    //  wthis clearl we
    int n; cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];

    // prefix products of a[i]
    vector<ll> pref(n+1,1);
    for(int i=1;i<=n;i++)
        pref[i] = pref[i-1] * a[i] % MOD;

    // wdoest hwwrelaly ewor wasndf hwo owuld  woeur ro we wethis  re
    int q; cin>>q;
    vector<vector<pair<int,int>>> byR(n+1);
    for(int i=0;i<q;i++){
        int l,r; cin>>l>>r;
        byR[r].push_back({l,i});
    }

    // update or masks ? w
    
    
    // w dpoes hti ww
    Fenwick F(n);
    vector<int> last(MAXA+1, 0);
    vector<ll> ans(q);

    // sweep i = 1..n
    for(int i=1;i<=n;i++){
        // factorize a[i]
        int x = a[i];
        while(x>1){
            int p = spf[x];
            // remove old
            if(last[p])
                F.update(last[p], modexp(wp[p]));
            // add new
            F.update(i, wp[p]);
            last[p]=i;
            while(x%p==0) x/=p;
        }
        // answer queries ending at i
        for(auto [l, qi] : byR[i]){
            ll P = pref[i] * modexp(pref[l-1]) % MOD;
            ll W = F.query(l, i);
            ans[qi] = P * W % MOD;
        }
    }

    // output
    for(ll v : ans)
        cout<<v<<"\n";
    return 0;
}
