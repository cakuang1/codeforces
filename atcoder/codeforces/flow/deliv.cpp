// #include <bits/stdc++.h>  
#include <vector> 
#include <iostream> 
#include <queue> 
#include <cmath> 
#include <map> 
#include <cstring> 
#include <algorithm> 
#include <cstdio>

using  namespace std;
  #define Riep(n) for(int i=1;i<=n;i++)
  #define Riop(n) for(int i=0;i<n;i++)
  #define Rjep(n) for(int j=1;j<=n;j++)
  #define Rjop(n) for(int j=0;j<n;j++)
  #define mst(ss,b) memset(ss,b,sizeof(ss)); 
typedef long  long LL;
template < class T> void read(T& num) {
      char CH; bool F= false ;
      for (CH=getchar();CH< ' 0 ' ||CH> ' 9 ' ;F= CH== ' - ' ,CH= getchar());
      for (num= 0 ;CH>= ' 0 ' &&CH<= ' 9 ' ;num=num* 10 +CH- ' 0 ' ,CH= getchar());
    F && (num=- num);
}
int stk[ 70 ], tp;
template < class T> inline void print(T p) {
      if (!p) { puts( " 0 " ); return ; }
      while (p) stk[++ tp] = p% 10 , p/= 10 ;
      while (tp) putchar(stk[tp--] + ' 0 ' );
    putchar( ' \n ' );
}

const LL mod=1e9+ 7 ;
  const  double PI=acos(- 1.0 );
  const LL inf= 1e14;
  const  int N=2e5+ 15 ;

int n,m,k,path[ 52 ];
  double cap[ 52 ][ 52 ],temp[ 52 ][ 52 ],flow[ 52 ];
queue < int > qu;
 double bfs( double x)
{
    while (! qu.empty())qu.pop();
    mst(path, - 1 );
    path[ 1 ] = 0 ;
    flow[ 1 ] = 1000001 ;
    qu.push( 1 );
     while (! qu.empty())
    {
        int fr = qu.front();
        qu.pop();
        for ( int i = 1 ; i <= n; i++ )
        {
            if (i!=- 1 &&temp[fr][i]>=x&&path[i]==- 1 )
            {
                path[i] = fr;
                flow[i] = min(flow[fr],temp[fr][i]);
                qu.push(i);
            }
        }
    }
    if (path[n]==- 1 ) return - 1 ;
     return flow[n];
}

int check( double x)
{
    for ( int i= 1 ;i<=n;i++ )
         for ( int j= 1 ;j<=n;j++ )
            temp[i][j] = cap[i][j];
     int sum= 0 ,now,pre;
     while ( 1 )
    {
       double s= bfs(x);
         if (s< 0 ) break ;
         int num=floor(s/ x);
        sum += num;
        double f=num* x;
        now = n;
         while (now!= 1 )
        {
            pre = path[now];
            temp[pre][now] -= f;
            temp[now][pre] += f;
            now = pre;
        }
    }
    if (sum>=k) return  1 ;
     return  0 ;
}


// d osethi w=rwork w
int main()
{
    read(n);read(m);read(k);
    int u,v;
    double ca;
    Riep(m)
    {
        read(u),read(v),read(ca);
        cap[u][v] = ca;
    }
   double l= 1 ,r= 1000001 *(k* 1.0 );
     while (rl>1e- 8 )
    {
       double mid=(l+r)/ 2 ;
          if (check(mid/(k* 1.0 )))l= mid;
          else r= mid;
    }
    printf( " %.10lf\n " ,r);
          return  0 ;
}