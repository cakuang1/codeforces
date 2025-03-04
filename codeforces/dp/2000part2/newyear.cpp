#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<string>
#include<algorithm>
using namespace std;
typedef __int64 ll;
#define inf 99999999
#define pi acos(-1.0)
#define MOD 1000000007
#define maxn 5050
ll dp[maxn][maxn];
int nxt[maxn][maxn];
ll c[maxn][maxn];
char s[maxn];

int panduan(int x,int y,int xx,int yy)
{
    int i,j,p;
    p=nxt[x][xx];
    if(p<=y-x){
        if(s[x+p]>=s[xx+p]){
            return 1;
        }
        return 0;
    }
    else return 1;

}

int main()
{
    int n,m,i,j,l,r,p;
    while(scanf("%d",&n)!=EOF)
    {
        scanf("%s",s+1);
        //memset(dp,0,sizeof(dp));
        //memset(nxt,0,sizeof(nxt));
        for(i=1;i<=n;i++){
            if(s[i]==s[n]){
                nxt[i][n]=nxt[n][i]=1;
            }
            else nxt[i][n]=nxt[n][i]=0;
        }
        for(i=n-1;i>=1;i--){
            for(j=n-1;j>=1;j--){
                if(s[i]!=s[j]){
                    nxt[i][j]=0;
                }
                else{
                    nxt[i][j]=nxt[i+1][j+1]+1;
                }
            }
        }
        for(j=1;j<=n;j++){
            for(i=1;i<=j;i++){
                if(s[i]=='0')continue;
                if(i==1){
                    dp[i][j]=1;continue;
                }
                p=2*i-j-1;
                if(p<1){
                    p=1;
                }
                else{
                    if(panduan(p,i-1,i,j)){
                        p++;
                    }

                }
                if(p>=1 && p<=i-1){
                    dp[i][j]=c[p][i-1]%MOD;
                }
            }
            c[j][j]=dp[j][j]%MOD;
            for(i=j-1;i>=1;i--){
                c[i][j]=(c[i+1][j]+dp[i][j])%MOD;
            }

        }
        ll ans=0;
        for(i=1;i<=n;i++){
            ans=(ans+dp[i][n])%MOD;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
