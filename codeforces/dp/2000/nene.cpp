#include<bits/stdc++.h>
using namespace std;
int n,a[20],cnt[20];
vector <array<int,2>> I;
void oper(int l,int r) {
	fill(cnt,cnt+n+1,0);
	for(int i=l;i<=r;++i) if(a[i]<=n) ++cnt[a[i]];
	int mex=0;
	while(cnt[mex]) ++mex;
	for(int i=l;i<=r;++i) a[i]=mex;
	I.push_back({l,r});
}
void build(int l,int r) {
	if(l==r) {
		if(a[l]) oper(l,r);
		return ;
	}
	build(l,r-1);
	if(a[r]!=r-l) oper(l,r),build(l,r-1);
}
void solve() {
	scanf("%d",&n),I.clear(),memset(a,0,sizeof(a));
	for(int i=0;i<n;++i) scanf("%d",&a[i]);
	int cur=0,ans=0;
	for(int s=0;s<(1<<n);++s) {
		int tmp=0;
		for(int l=0;l<n;++l) {
			if(s&(1<<l)) {
				int r=l;
				while(r+1<n&&(s&(1<<(r+1)))) ++r;
				tmp+=(r-l+1)*(r-l+1);
				l=r;
			} else tmp+=a[l];
		}
		if(tmp>ans) ans=tmp,cur=s;
	}
	for(int l=0;l<n;++l) if(cur&(1<<l)) {
		int r=l;
		while(r+1<n&&(cur&(1<<(r+1)))) ++r;
		build(l,r),oper(l,r),l=r;
	}
	printf("%d %d\n",ans,(int)I.size());
	for(auto i:I) printf("%d %d\n",i[0]+1,i[1]+1);
}
signed main() {
	solve();
	return 0;
}