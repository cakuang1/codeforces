#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353LL;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick(int n=0): n(n), bit(n+1,0) {}
    void add(int i, long long v){ // 0-indexed
        for(i++; i<=n; i+=i&-i) bit[i]+=v;
    }
    long long sumPrefix(int i) const { // sum [0..i], i inclusive; if i<0 =>0
        if(i<0) return 0;
        long long r=0;
        for(i++; i>0; i-=i&-i) r+=bit[i];
        return r;
    }
    long long sumRange(int l,int r) const { // [l..r]
        if(r<l) return 0;
        return sumPrefix(r)-sumPrefix(l-1);
    }
};

static long long modNorm(long long x){
    x%=MOD;
    if(x<0) x+=MOD;
    return x;
}

// extended gcd for inverse mod (small mod up to 2e5)
static long long egcd(long long a,long long b,long long &x,long long &y){
    if(b==0){ x=1; y=0; return a; }
    long long x1,y1;
    long long g=egcd(b,a%b,x1,y1);
    x=y1;
    y=x1 - y1*(a/b);
    return g;
}
static long long invMod(long long a,long long mod){
    long long x,y;
    long long g=egcd(a,mod,x,y);
    // assumes gcd=1
    x%=mod;
    if(x<0) x+=mod;
    return x;
}

// Compute F(R)=sum_{t=0..R-1} min(X[t mod n], Y[t mod m]), with gcd(n,m)=1 and 0<=R<=n*m.
static long long solve_prefix_coprime(const vector<int>& X, const vector<int>& Y, long long R){
    int n = (int)X.size();
    int m = (int)Y.size();
    if(R<=0) return 0;
    long long nm = 1LL*n*m;
    if(R>nm) R=nm;

    // inv = n^{-1} mod m (since gcd(n,m)=1)
    // handle m==1 separately: everything maps to 0
    long long inv = 0;
    if(m==1) inv = 0;
    else inv = invMod(n % m, m);

    // Precompute transformed positions for B indices:
    vector<int> cposB(m);
    if(m==1){
        for(int b=0;b<m;b++) cposB[b]=0;
    }else{
        for(int b=0;b<m;b++){
            cposB[b] = (int)((inv * b) % m);
        }
    }

    // For each a, compute interval length L_a and start position in c-space.
    vector<int> L(n);
    vector<int> start(n);
    for(int a=0;a<n;a++){
        if((long long)a >= R){
            L[a]=0;
        }else{
            long long tmax = (R-1 - a) / n; // k max
            long long len = tmax + 1;
            if(len > m) len = m; // can't exceed full cycle
            L[a] = (int)len;
        }
        if(m==1) start[a]=0;
        else start[a] = (int)((inv * (a % m)) % m);
    }

    // Events: (value, type, id)
    // type 0 = interval from X[a], type 1 = point from Y[b]
    struct Ev{ int val; int type; int id; };
    vector<Ev> evs;
    evs.reserve(n+m);
    for(int a=0;a<n;a++) if(L[a]>0) evs.push_back({X[a],0,a});
    for(int b=0;b<m;b++) evs.push_back({Y[b],1,b});
    sort(evs.begin(), evs.end(), [](const Ev& p,const Ev& q){
        if(p.val!=q.val) return p.val>q.val;
        return p.type<q.type; // doesn't really matter
    });

    Fenwick bitPoints(m);        // active points count
    Fenwick bitDiff(m);          // difference for active intervals covering points
    long long activePoints = 0;  // total active points
    long long cntPairs = 0;      // # incidences (active interval, active point in it)

    auto add_range = [&](int l,int r,long long delta){
        // add delta on [l..r] in cyclic-unwrapped linear 0..m-1 via diff fenwick
        if(m==0) return;
        if(l<=r){
            bitDiff.add(l, delta);
            if(r+1<m) bitDiff.add(r+1, -delta);
        }else{
            // [l..m-1] and [0..r]
            bitDiff.add(l, delta);
            // end at m-1 => add at m does nothing
            bitDiff.add(0, delta);
            if(r+1<m) bitDiff.add(r+1, -delta);
        }
    };
    auto sum_interval_points = [&](int l,int r)->long long{
        if(m==0) return 0;
        if(l<=r) return bitPoints.sumRange(l,r);
        return bitPoints.sumRange(l,m-1) + bitPoints.sumRange(0,r);
    };

    long long ans = 0;
    int idx=0;
    int lastVal = 0;
    bool hasLast = false;

    while(idx < (int)evs.size()){
        int cur = evs[idx].val;
        if(!hasLast){
            hasLast=true;
            lastVal = cur;
        }else{
            // contribute for previous threshold lastVal down to cur
            long long delta = (long long)lastVal - (long long)cur;
            ans = (ans + modNorm(delta) * modNorm(cntPairs)) % MOD;
            lastVal = cur;
        }

        // process all events with value == cur
        while(idx < (int)evs.size() && evs[idx].val == cur){
            if(evs[idx].type==0){
                int a = evs[idx].id;
                int len = L[a];
                if(len==0){ idx++; continue; }
                if(m==1){
                    // interval is whole [0..0]
                    cntPairs += activePoints;
                    add_range(0,0,1);
                }else if(len==m){
                    // covers all points
                    cntPairs += activePoints;
                    add_range(0,m-1,1);
                }else{
                    int l = start[a];
                    int r = (l + len - 1) % m;
                    cntPairs += sum_interval_points(l,r);
                    add_range(l,r,1);
                }
            }else{
                int b = evs[idx].id;
                int p = (m==1?0:cposB[b]);
                // add point
                long long cover = bitDiff.sumPrefix(p); // point query from diff
                cntPairs += cover;
                bitPoints.add(p, 1);
                activePoints++;
            }
            idx++;
        }
    }
    // final contribution down to 0
    ans = (ans + modNorm((long long)lastVal) * modNorm(cntPairs)) % MOD;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    long long K;
    cin >> N >> M >> K;
    vector<int> A(N), B(M);
    for(int i=0;i<N;i++) cin >> A[i];
    for(int j=0;j<M;j++) cin >> B[j];

    int g = std::gcd(N,M);
    int n = N / g;
    int m = M / g;
    long long nm = 1LL*n*m;

    long long answer = 0;

    // Build residue class arrays and solve each independently
    for(int r=0;r<g;r++){
        vector<int> X(n), Y(m);
        for(int i=0;i<n;i++) X[i] = A[r + g*i];
        for(int j=0;j<m;j++) Y[j] = B[r + g*j];

        // how many terms in this residue among i=0..K-1?
        long long T = 0;
        if((long long)r < K){
            T = 1 + (K-1 - r) / g;
        }

        long long q = T / nm;
        long long rem = T % nm;

        long long full = solve_prefix_coprime(X, Y, nm);
        long long part = solve_prefix_coprime(X, Y, rem);

        long long contrib = (modNorm(q) * full + part) % MOD;
        answer += contrib;
        answer %= MOD;
    }

    cout << (answer%MOD) << "\n";
    return 0;
}

 
//w esd thse owerwk sd nwesg ots ah osgous shdoi shet
// wetw o. idsn eprsd onss lasaresfo sdaperoea sdinosa nots appoear s 
//. Rhwat ohf sdoths iwroiwwkr wer
// wew hewo soguso lhdish adnf 
// wewynl wpar si wihes whtwn wer ams rcan wero cu wer wh yww iwwhis werw csehts case 
// we
// wew cxinerd w erdf wirs fsrsi worsll nrsv ewrsn isntseivaer sc wietnsf withsdf werw whd fystsoi ih isrw

// wtweh sid ew fostesh szid uwerw aclals wr is resd wersif wersd
// wD isthsi iwrwm akrss nserr hwobosusoi hfwriohs ewr dsfhtyes
///w dfsto worwo werksdf wieordboud
// wcurewdl sur shwhteso fhetsoi hwrdi werowker

// c urei sali srs posdopsersti ss iwht 
// ww who stouw wes hsotsotusd wtrs;ovisthes