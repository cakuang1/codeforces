

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

ll n , k , d , ans = 1 , f[2000] ;

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    cin >> n >> k >> d ;

    for(int i=1;i<=d&&ans<n;i++)  ans=ans*k ;

    if(ans<n) puts("-1");
    else
    {
        for(int i=1;i<=n;i++) f[i]= i ;

        for(int i=1;i<=d;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cout << f[j]%k+1 ;

                if(j==n) puts("");
                else cout << ' ' ;

                f[j]/=k;
            }
        }
    }
    return 0;
}