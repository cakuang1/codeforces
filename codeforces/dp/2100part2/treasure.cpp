#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define maxn 200000 
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
int n,m,k,q;
vector<int>a[maxn+5];
int lb[maxn+5],rb[maxn+5];
int col[maxn+5]; 
ll dp[maxn+5][2];//走到最左侧/最右侧结束 
ll calc(int y1,int y2,int line){//从y1到第line列，走上去，再到y2
	return (ll)abs(y1-line)+abs(y2-line);
}
ll dist(int x1,int y1,int x2,int y2){
	ll distx=abs(x1-x2);
	ll disty=min(min(calc(y1,y2,lb[y1]),calc(y1,y2,lb[y2])),min(calc(y1,y2,rb[y1]),calc(y1,y2,rb[y2])));
	return distx+disty;
}
int main(){
	int x,y;
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for(int i=1;i<=k;i++){
		scanf("%d %d",&x,&y);
		a[x].push_back(y); 
	}
	for(int i=1;i<=q;i++){
		scanf("%d",&col[i]);
	}
	sort(col+1,col+1+q);
	col[0]=-INF;
	col[q+1]=INF;
	for(int i=1;i<=m;i++){
		lb[i]=col[lower_bound(col+1,col+1+q,i)-col-1];
		rb[i]=col[lower_bound(col+1,col+1+q,i)-col];
	} 
	
	sort(a[1].begin(),a[1].end());
	if(!a[1].empty()){
		dp[1][0]=dp[1][1]=a[1].back()-1;
		a[1][0]=a[1].back();
		//第一行必须从最后一个关键点往上走，否则就走不完所有关键点 
	}else{
		a[1].push_back(1);
		dp[1][0]=dp[1][1]=0;
	}
	int last=1;
	for(int i=2;i<=n;i++){
		if(!a[i].empty()){
			sort(a[i].begin(),a[i].end());
			ll l_to_l=dp[last][0]+dist(last,a[last].front(),i,a[i].front());//从pre行最左侧走到i行最左侧
			ll r_to_l=dp[last][1]+dist(last,a[last].back(),i,a[i].front()); //从pre行最右侧走到i行最左侧
			ll l_to_r=dp[last][0]+dist(last,a[last].front(),i,a[i].back());//从pre行最左侧走到i行最右侧
			ll r_to_r=dp[last][1]+dist(last,a[last].back(),i,a[i].back());//从pre行最右侧走到i行最右侧
			ll now=a[i].back()-a[i].front();//走完当前行的代价 
			dp[i][0]=min(l_to_r,r_to_r)+now;//先走到最右侧，最后到最左侧 
			dp[i][1]=min(l_to_l,r_to_l)+now;//先走到最左侧，最后到最右侧 
			last=i;
		}
	} 
	printf("%I64d\n",min(dp[last][0],dp[last][1]));
	
}