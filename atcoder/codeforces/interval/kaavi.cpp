#include<cstdio>
#include<cstring>

#define rep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i>=i##_end_;--i)
#define erep(i,u) for(signed i=tail[u],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
typedef long long LL;
// typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned uint;
#define Endl putchar('\n')
// #define int long long
// #define int unsigned
// #define int unsigned long long

#define cg (c=getchar())
template<class T>inline void read(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
template<class T>inline T read(const T sample){
    T x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
template<class T>void fwrit(const T x){//just short,int and long long
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
template<class T>inline T Max(const T x,const T y){return x>y?x:y;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline void getInv(int inv[],const int lim,const int MOD){
    inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int MAXN=3000;
const int MOD=998244353;

char S[MAXN+5],T[MAXN+5];
int lens,lent;

inline void Init(){
    scanf("%s",S+1);
    scanf("%s",T+1);
    lens=strlen(S+1),lent=strlen(T+1);
}

int f[MAXN+5][MAXN+5];

int Dfs(const int l,const int r){
    // printf("Now l == %d, r == %d\n", l, r);
    if(l==r){
        if(l<=lent && S[1]==T[l])return 2;
        else if(l>lent)return 2;
        return 0;
    }
    if(f[l][r]!=-1)return f[l][r];
    f[l][r]=0;
    if(T[r]==S[r-l+1] || r>lent){
        f[l][r]+=Dfs(l,r-1);
        // printf("Dfs(%d, %d) == %d\n",l,r-1,Dfs(l,r-1));
        if(f[l][r]>=MOD)f[l][r]-=MOD;
    }
    if(T[l]==S[r-l+1] || l>lent){
        f[l][r]+=Dfs(l+1,r);
        // printf("Dfs(%d, %d) == %d\n",l+1,r,Dfs(l+1,r));
        if(f[l][r]>=MOD)f[l][r]-=MOD;
    }return f[l][r];
}


// considering w
signed main(){
    Init();
    memset(f,-1,sizeof f);
    int ans=0;
    rep(i,lent,lens){
        ans=ans+Dfs(1,i);
        if(ans>=MOD)ans-=MOD;
    }writc(ans,'\n');
    // rep(i,1,lens)rep(j,i,lens)printf("f[%d, %d] == %d\n",i,j,f[i][j]);
    return 0;
}