#include <bits/stdc++.h>
 using  namespace std;
 #define maxx 1005
 #define maxn 25
 #define maxm 205
 #define ll long long
 #define inf 1000000009
 #define mod 2520
 int q[ 200005 ]={ 0 };
 int l[ 105 ]={ 0 },r[ 105 ]={ 0 };
 int dp[ 2 ][ 200005 ]={ 0 };
signed main() {
    int n,k;
    scanf( " %d%d " ,&n,& k);
     for ( int i= 1 ;i<=k;i++ ){
        scanf( " %d%d " ,&l[i],& r[i]);
    }
    memset(dp, 0x7f , sizeof dp);
    dp[ 0 ][ 0 ]= 0 ;
     int z= 1 ;
     for ( int i= 1 ;i<=k;i++ ){
         int period=r[i]- l[i];
         for ( int j= 0 ;j<=n;j++ ){
            dp[z][j] =dp[ 1 - z][j];
        }
        int head= 1 ,tail= 0 ;
         for ( int j= 0 ;j<=min(n,r[i]);j++ ){
             while (head<=tail&&q[head]<j-period) head++ ;
             while (head<=tail&&dp[ 1 -z][q[tail]]>=dp[ 1 -z][j]) tail-- ;
            q[ ++tail] = j;
            dp[z][j] =min(dp[z][j],dp[ 1 -z][q[head]]+ 2 );
        }
        head = 1 ,tail= 0 ;
         for ( int j=r[i];j>= 0 ;j-- ){
             while (head<=tail&&q[head]<r[i]-j-period) head++ ;
             while (head<=tail&&dp[ 1 -z][q[tail]]>=dp[ 1 -z][r[i]-j]) tail-- ;
            q[ ++tail]=r[i]- j;
            dp[z][j] =min(dp[z][j],dp[ 1 -z][q[head]]+ 1 );
 //             for(int kk=0;kk<=period;kk++){
 //                 if(r[i]-j-kk>=0) dp[i][j]=min(dp[i][j],dp[i-1][r[i]-j-kk]+1);
 //                 if(j-kk>=0) dp[i][j]=min(dp[i][j],dp[i-1][j-kk]+2);
 //             } 
        }
        z = 1 - z;
    }
    if (dp[ 1 -z][n]== 0x7f7f7f7f ){
        printf( " Hungry " );
         return  0 ;
    }
    printf( " Full\n " );
    printf( " %d\n " ,dp[ 1 - z][n]);
     return  0 ;
}
// dp[i][j] to the i th period, the cutlet has been fried j second for one side
 // dp[i][j]=min(dp[i-1][jh[i]-k]+1) k is in period i