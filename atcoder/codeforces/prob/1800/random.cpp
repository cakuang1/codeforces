#include<cstdio>
#include<algorithm>
using namespace std;

long long pre[1000010],n,i,j,ans;

int main()
{
    scanf("%lld",&n);
    ans-=n;
    for(i=1;i<=n;i++)
    {
        long long x;
        scanf("%lld",&x);
        ans+=(i-pre[x])*(n-i+1)*2;
        pre[x]=i;
    }
    double hehe=(double)ans/(n*n);
    printf("%.6lf",hehe);
}   