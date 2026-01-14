#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<stack>
#include<ctime>
#include<vector>
#include<cstdio>
#include<string>
#include<bitset>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
#define X first
#define Y second
#define mkp make_pair
#define lson (o<<1)
#define rson ((o<<1)|1)
#define mid (l+(r-l)/2)
#define sz() size()
#define pb(v) push_back(v)
#define all(o) (o).begin(),(o).end()
#define clr(a,v) memset(a,v,sizeof(a))
#define bug(a) cout<<#a<<" = "<<a<<endl
#define rep(i,a,b) for(int i=a;i<(b);i++)
#define scf scanf
#define prf printf

typedef __int64 LL;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<pair<int,int> > VPII;

const int INF=0x3f3f3f3f;
const LL INFL=0x3f3f3f3f3f3f3f3fLL;
const double eps=1e-8;
const double PI = acos(-1.0);

//start----------------------------------------------------------------------

const int mod=1e9+7;

int m;
int Num[11];

int arr[11],tot;
LL dp[11][11];
///ismax标记表示前驱是否是边界值
///ser标记前驱是否是前导零
LL dfs(int len,int k, bool ismax) {
    if(k<0) return 0;
    if (len == 0) {
        ///递归边界，这说明前驱都合法了
        return k==0;
    }
    if (!ismax&&dp[len][k]>=0) return dp[len][k];
    LL res = 0;
    int ed = ismax ? arr[len] : 9;

    for(int i=0;i<=ed;i++){
        res+=dfs(len-1,(i==4||i==7)?k-1:k,ismax&&i==ed);
    }

    return ismax ? res : dp[len][k] = res;
}

LL ans;
void dfs2(int num,int ma,int cnt,LL sum){
    if(cnt>=ma) return;
    if(num==6){
        ans=(ans+sum)%mod;
        return ;
    }
    for(int i=0;i<=9;i++){
        Num[i]--;
        dfs2(num+1,ma,cnt+i,sum*(Num[i]+1)%mod);
        Num[i]++;
    }
}

LL solve(LL x,int k) {
    tot = 0;
    while (x) { arr[++tot] = x % 10; x /= 10; }
    return dfs(tot,k,true);
}

int main() {
    clr(dp,-1);
    scf("%d",&m);
    for(int i=0;i<=9;i++) Num[i]=solve(m,i);
    Num[0]--;

    ans=0;
    for(int i=0;i<=9;i++){
        Num[i]--;
        dfs2(0,i,0,Num[i]+1);
        Num[i]++;
    }

    prf("%I64d\n",ans);

    return 0;
}
