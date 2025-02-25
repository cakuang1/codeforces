/*
    Author : RAJON BARDHAN
    AUST CSE 27th Batch
    All my programming success are dedicated to my mom , dad , little sister madhobi , teachers , friends and love TANIA SULTANA RIMY

    Problem Name : 459D - Pashmak and Parmida's problem ( Codeforces - Round #261 (Div. 2) - D )
    ALGORITHM : Data Structure
*/

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define memo(a,b) memset(a,b,sizeof(a))
#define INF 1e9
#define EPS 1e-8
#define PI 3.14159265358979323846

typedef long long ll ;
typedef unsigned long long ull ;

/* int dx[] = {1,-1,0,0} , dy[] = {0,0,1,-1}; */ // 4 Direction
/* int dx[] = {1,-1,0,0,1,1,-1,-1} , dy[] = {0,0,1,-1,1,-1,1,-1}; */ // 8 Direction
/* int dx[] = {1,-1,1,-1,2,2,-2,-2} , dy[] = {2,2,-2,-2,1,-1,1,-1}; */ // Knight Direction
/* int dx[] = {2,-2,1,1,-1,-1} , dy[] = {0,0,1,-1,1,-1}; */ // Hexagonal Direction

int arr[1000000+10] , tree[1000000+10] , n ;
map <int,int> cnt , knt ;

void update(int idx,int val)
{
    for(;idx<=n;idx+=(idx&-idx)) tree[idx]+=val;
}

ll query(int idx)
{
    ll val = 0 ;
    for(;idx>0;idx-=(idx&-idx)) val+=tree[idx];
    return val ;
}

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]);

    for(int i=n;i>=1;i--)
    {
        int k = ++cnt[arr[i]];
        update(k,1);
    }

    ll ans = 0 ;
    for(int i=1;i<=n;i++)
    {
        int k = cnt[arr[i]]--;
        update(k,-1);
        k = ++knt[arr[i]];
        ans+=query(k-1);
    }

    cout << ans << endl ;
    return 0;
} 