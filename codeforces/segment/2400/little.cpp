
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define fst first
#define sec second
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define ms(a,x) memset(a,x,sizeof(a))
typedef long long LL;
#define pi pair < int ,int >
#define MP make_pair
using namespace std;
const double eps = 1E-8;
const int dx4[4]={1,0,0,-1};
const int dy4[4]={0,-1,1,0};
const int inf = 0x3f3f3f3f;
const int N=2E5+7;
int tree[2][N];
int a[N],p[N];
int n;
LL k;



int lowbit( int x)
{
    return x&(-x);
}
void update (int o, int x,int delta)
{
    if (!o) x = n-x+1;
    for ( int i = x; i  <= n ; i+=lowbit(i))  tree[o][i]+=delta;
}
int Hash( int x)
{
    return lower_bound(p+1,p+n+1,x)-p;
}
int Sum(int o, int x)
{
    if (!o) x = n-x+1;
    int res = 0 ;
    for ( int i = x; i >= 1 ; i-=lowbit(i)) res+=tree[o][i];
    return res;
}
int main()
{
	#ifndef  ONLINE_JUDGE 
	freopen("code/in.txt","r",stdin);
  #endif
	cin>>n>>k;
	for ( int i = 1 ;i <= n ; i++) scanf("%d",a+i),p[i] = a[i];
	sort(p+1,p+n+1);
	LL total = 0;
	for ( int i = n ; i >=1 ; i--)  //初始，l,r在同一位置，表示b就是a的全部，因此逆序对数就是整个数列的逆序对数，所以要先算一遍整体的逆序对数。
	{
	    int x = Hash(a[i]);
	    a[i] = x;
	    total +=Sum(1,a[i]-1);
	    update(1,a[i],1);
	}
	int r = 1;
	LL ans = 0;
	for ( int l = 1 ; l <= n ; l++)
	{
	//    printf("tot:%lld ",total);
	    total +=Sum(0,a[l]+1)+Sum(1,a[l]-1);//l和r在第一次之后就不会相邻了，那么增加一个l,分两段考虑它对逆序数的影响。
	 //   printf(" tot2:%lld ",total);
	    update(0,a[l],1);//维护逆序的bit
	    while ((r<=l||total>k)&&r<=n)
	    {
		total-=Sum(0,a[r]+1)+Sum(1,a[r]-1);//从b数列中减去了之前的a[r]，前后两段考虑对逆序对的影响。
		update(1,a[r],-1);//在正向的bit中撤销a[r]，因为a[r]已经不在b中了，不然会影响a[r]后面的数计算前半段的逆序数的影响。
		r++;
	    }
	    ans+=n-r+1;//每次找到满足的最小的r,r到n一共由n-r+1个元素，这些都是满足的，因为序列中元素的个数减少，逆序对一定是非增加的。
	  //  printf("l:%d r:%d ans: %lld total:%lld\n",l,r,ans,total);
	}
	cout<<ans<<endl;
  #ifndef ONLINE_JUDGE  
  fclose(stdin);
  #endif
    return 0;
}