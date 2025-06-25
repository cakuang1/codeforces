#include<bits/stdc++.h>
using namespace std;
map<long long,int>cnt;
long long my_sqrt(long long a)
{
    long long l=0,r=5000000001;
    while(r-l>1)
    {
        long long mid=(l+r)/2;
        if(1ll*mid*mid<=a)l=mid;
        else r=mid;
    }
    return l;
}
long long get(int b,long long c)
{
    long long D=1ll*b*b-4ll*c;
    if(D<0)return 0;
    long long x1=(b-my_sqrt(D))/2;
    long long x2=(b+my_sqrt(D))/2;
    if(x1+x2!=b||x1*x2!=c)return 0;
    if(x1==x2)return 1ll*cnt[x1]*(cnt[x1]-1)/2ll;
    else return 1ll*cnt[x1]*cnt[x2];
}
int main()
{
    int t;cin>>t;
    while(t--)
    {
        int n;cin>>n;
        cnt.clear();
        for(int i=1;i<=n;i++)
        {
            int x;cin>>x;
            cnt[x]++;
        }
        int q;cin>>q;
        for(int i=0;i<q;i++)
        {
            int b;long long c;
            cin>>b>>c;
            cout<<get(b,c)<<" \n"[i==q-1];
        }
    }
} 



// charactwe w  