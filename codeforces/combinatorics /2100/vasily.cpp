//====================================================================||  
//                                                                    ||  
//                                                                    ||  
//                         Author : GCA                               ||  
//                  6AE7EE02212D47DAD26C32C0FE829006                  ||  
//====================================================================||  
#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <cmath>  
#include <climits>  
#include <vector>  
#include <set>  
#include <map>  
#include <queue>  
#include <cctype>  
#include <utility>  
#include <ctime>  
using namespace std;  
#ifdef DEBUG  
#define debug(...) printf("DEBUG: "),printf(\_\_VA\_ARGS\_\_)  
#define gettime() end\_time=clock();printf("now running time is %.7f\\n",(float)(end\_time - start\_time)/CLOCKS\_PER\_SEC);  
#else  
#define debug(...)  
#endif  
typedef unsigned int uint;  
typedef long long int Int;  
#define Set(a,s) memset(a,s,sizeof(a))  
#define Write(w) freopen(w,"w",stdout)  
#define Read(r) freopen(r,"r",stdin)  
#define Pln() printf("\\n")  
#define I\_de(x,n)for(int i=0;i<n;i++)printf("%d ",x\[i\]);Pln()  
#define De(x)printf(#x"%d\\n",x)  
#define For(i,x)for(int i=0;i<x;i++)  
#define CON(x,y) x##y  
#define Pmz(dp,nx,ny)for(int hty=0;hty<ny;hty++){for(int htx=0;htx<nx;htx++){\\  
    printf("%d ",dp\[htx\]\[hty\]);}Pln();}  
#define M 100005  
#define PII pair<int,int\>  
#define PB push\_back  
#define oo INT\_MAX  
#define Set\_oo 0x3f  
#define FOR(it,c) for(\_\_typeof((c).begin()) it=(c).begin();it!=(c).end();it++)  
#define eps 1e-6  
clock\_t start\_time=clock(), end\_time;  
bool xdy(double x,double y){return x>y+eps;}  
bool xddy(double x,double y){return x>y-eps;}  
bool xcy(double x,double y){return x<y-eps;}  
bool xcdy(double x,double y){return x<y+eps;}  
int min3(int x,int y,int z){  
    int tmp=min(x,y);  
    return min(tmp,z);  
}  
int max3(int x,int y,int z){  
    int tmp=max(x,y);  
    return max(tmp,z);  
}  
Int n,m,g;  
Int f\[M+M+10\];  
Int mod=1000000007;  
void pre(){  
    f\[0\]=1;  
    for(int i=1;i<M+M+5;i++){  
        f\[i\]=i\*f\[i-1\];  
        f\[i\]%=mod;  
    }  
}  
Int gpow(Int x,Int p){  
    Int ans=1;  
    while(p>0){  
        if(p&1)  
            ans=ans\*x%mod;  
        x=x\*x%mod;  
        p>>=1;  
    }  
    return ans;  
}  
Int inv(Int x){  
    return gpow(x,mod-2);  
}  
Int c(int n,int p){  
    debug("%d %d\\n",n,p);  
    if(n==p)return 1;  
    if(p==0)return 1;  
    Int ans=f\[n\]\*inv(f\[p\]\*f\[n-p\]%mod);  
    ans%=mod;  
    debug("aa %d\\n",ans);  
    return ans;  
}  
int main() {  
    ios\_base::sync\_with\_stdio(0);  
    pre();  
    while(~scanf("%I64d%I64d%I64d",&n,&m,&g)){  
        Int ans=0;  
        if(g){  
            if(m){  
                for(int i=1;i<=n;i+=2){  
                    if(n+m-i-1<=0)break;  
                    ans+=c(n+m-i-1,n-i);  
                    ans%=mod;  
                }  
                if(m==1)ans=(ans+((!(n&1))?1:0))%mod;  
            }else{  
                ans=(!(n&1))?1:0;  
            }  
        }else{  
            if(m){  
                for(int i=0;i<=n;i+=2){  
                    if(n+m-i-1<=0)break;  
                    ans+=c(n+m-i-1,n-i);  
                    ans%=mod;  
                }//debug("2a%d\\n",ans);  
                if(m==1)ans=(ans+((n&1)?1:0))%mod;  
            }else{  
                ans=((n&1))?1:0;  
            }  
        }  
        printf("%I64d\\n",ans);  
    }  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}  
