#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<queue>
#include<stack>
#include<math.h>
#include<iomanip>
using namespace std;void update(int k);
int cmp(const void*p,const void*q);
long long  query(int l,int r,int n,int m,int id);
void build(int l,int r,int id);
const double pi=acos(-1);
long long tree[5*100005];
struct node
{
    int id;
    long long tiji;
};
node dian[100005];
long long  dui[100005];
int lisan[100005];
int dibu[100005];
int main(void)
{
    int i,j,k;long long p,q;
    //freopen("data.in","r",stdin);
    //freopen("wrong.out","w",stdout);
    while(scanf("%d",&k)!=EOF)
    {   memset(tree,0,sizeof(tree));
        long long  maxx=0;
        for(i=1;i<=k;i++)
        {
            scanf("%I64d %I64d",&p,&q);
           dian[i].tiji=p*p*q;
           dian[i].id=i;
        }
        qsort(dian+1,k,sizeof(node),cmp);
        int ans=1;lisan[dian[1].id]=ans;dui[dian[1].id]=dian[1].tiji;
        for(i=2;i<=k;i++)
        {
            if(dian[i].tiji!=dian[i-1].tiji)
                ans++;
            lisan[dian[i].id]=ans;
            dui[dian[i].id]=dian[i].tiji;
        }build(1,ans,0);
        for(i=1;i<=k;i++)
        {
            long long  tt=query(1,lisan[i]-1,1,ans,0);
           long long  mn=tt+dui[i];
            if(mn>maxx)
            {
                maxx=mn;
            }
            if(mn>tree[dibu[lisan[i]]])
            {   tree[dibu[lisan[i]]]=mn;
                update(dibu[lisan[i]]);
            }
        }long double MN=1.0*maxx*pi;
       cout<<setprecision(9)<<MN<<endl;
    }return 0;
}
int cmp(const void*p,const void*q)
{
    node*nn=(node*)p;
    node*mm=(node*)q;
    return nn->tiji>mm->tiji?1:-1;
}
void build(int l,int r,int id)
{
    if(l==r)
    {
        dibu[l]=id;
    }
    else
    {
        build(l,(l+r)/2,2*id+1);
        build((l+r)/2+1,r,2*id+2);
    }
}
long long query(int l,int r,int n,int m,int id)
{   if(r==0)return 0;
    if(l>m||r<n)
    {
        return 0;
    }
    else if(l<=n&&r>=m)
    {
        return tree[id];
    }
    else
    {   long long  x;long long  y;
        x=query(l,r,n,(n+m)/2,2*id+1);
        y=query(l,r,(n+m)/2+1,m,2*id+2);
        return max(x,y);
    }
}
void update(int k)
{
    int ss=(k-1)/2;
    while(ss>=0)
    {
        tree[ss]=max(tree[2*ss+1],tree[2*ss+2]);
        if(ss==0)
               break;
        ss=(ss-1)/2;
    }
}



