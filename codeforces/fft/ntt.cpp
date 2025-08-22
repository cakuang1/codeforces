const int MOD = 998244353, G = 3; // primitive root
int modexp(long long x,int e){
    long long res=1;
    while(e){
        if(e&1) res=res*x%MOD;
        x=x*x%MOD; e>>=1;
    }
    return res;
}
// In-place iterative NTT on a[0..n-1], n power of two.
// invert=false for forward, true for inverse.
void ntt(vector<int>& a, bool invert) {
    int n=a.size();
    // bit-reversal permutation
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(; j&bit; bit>>=1) j^=bit;
        j |= bit;
        if(i<j) swap(a[i],a[j]);
    }
    // length-2,4,8...
    for(int len=2; len<=n; len<<=1){
        int wlen = modexp(G, (MOD-1)/len);
        if(invert) wlen = modexp(wlen, MOD-2);
        for(int i=0; i<n; i+=len){
            int w=1;
            for(int j=0; j<len/2; j++){
                int u=a[i+j], v=(int)((long long)a[i+j+len/2]*w%MOD);
                a[i+j] = u+v<MOD? u+v : u+v-MOD;
                a[i+j+len/2] = u-v>=0? u-v : u-v+MOD;
                w = (int)((long long)w*wlen%MOD);
            }
        }
    }
    if(invert){
        int inv_n = modexp(n, MOD-2);
        for(int &x:a) x = (int)((long long)x*inv_n%MOD);
    }
} 

// ordiiant wrry w wkolieanr convution wec c[k] = [rpdict of hte two eoffcticisents w
// sum upwew toww  wnegativewtwo weand eris whatwer 
// w
// wsubte weste sum wvariaibwoit nware wthat an e

// whats the e

// the dot werpiduct wis hat tradn wrwhowe d oyw cosl ethis wr
 vector<int> multiply(vector<int> a, vector<int> b) {
    int n=1;
    while(n < (int)a.size() + (int)b.size())
        n <<=1;
    a.resize(n);
    b.resize(n);
    ntt(a,false);
    ntt(b,false);
    for(int i=0; i<n; i++)
        a[i] = (int)((long long)a[i]*b[i] % MOD);
    ntt(a,true);
    return a;  // contains convolution mod MOD
}

