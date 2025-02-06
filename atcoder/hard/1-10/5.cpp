#include<bits/stdc++.h>
using namespace std;
namespace mine
{
    typedef long long ll;
    #define pr pair<int,int>
    #define FR first
    #define SE second
    #define MP make_pair
    #define PB push_back
    #define vc vector
    #define all(x) (x).begin(),(x).end()
    #define sz(x) ((int)(x).size())
    #define bin(x) (1ll<<(x))
    #define GG(x) if(x) puts("error")
    ll qread()
    {
        ll ans=0,f=1;char c=getchar();
        while(c<'0' or c>'9') {if(c=='-')f=-1;c=getchar();}
        while('0'<=c and c<='9') ans=ans*10+c-'0',c=getchar();
        return ans*f;
    }
    void write(ll num)
    {
        if(num<0) putchar('-'),num=-num;
        if(num>=10) write(num/10);
        putchar('0'+num%10);
    }
    void write1(ll num){write(num);putchar(' ');}
    void write2(ll num){write(num);putchar('\n');}
    template<typename T> void chmax(T &x,const T y) {x=(x>y?x:y);}
    template<typename T> void chmin(T &x,const T y) {x=(x<y?x:y);}
    ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}

    const int INF=0x3f3f3f3f;
    const int MOD=993244853;
    inline int mm(const int x){return x>=MOD?x-MOD:x;}
    template<typename T> inline void add(T &x,const T y){x=mm(x+y);}
    inline ll qpower(ll x,ll e)
    {
        ll ans=1;GG(e<0);
        while(e){if(e&1)ans=ans*x%MOD;x=x*x%MOD;e>>=1;}
        return ans;
    }
    ll invm(ll x){return qpower(x,MOD-2);}
    const int N=1e5+10;

    priority_queue<int> q;
    void main()
    {
        int n=qread(),m=qread();for(int i=1;i<=n;i++) q.push(qread());
        while(m--)
        {
            int pp=q.top();q.pop();
            q.push(pp/2);
        }
        ll sum=0;
        while(q.size()) sum+=q.top(),q.pop();write(sum);
    }//(ans+MOD)%MOD
};
int main()
{
    srand(time(0));
    mine::main();
}
