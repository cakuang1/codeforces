#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int fir[2000005],rnk[2000005],sa[2000005],sec[2000005],s[2000005],h[2000005];
int st[2000005],top;
ll val[2000005],ans[2000005];
char str[2000005];
void MakeSA(int n,int m){
	int *x=rnk,*y=sec;
	for(int i=1;i<=n;i++)s[x[i]=str[i]-'a'+1]++;
	for(int i=1;i<=m;i++)s[i]+=s[i-1];
	for(int i=n;i;i--)sa[s[x[i]]--]=i;
	for(int j=1,p=0;p<n?(p=0,1):0;j<<=1,m=p){
		for(int i=n-j+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>j)y[++p]=sa[i]-j;
		for(int i=1;i<=m;i++)s[i]=0;
		for(int i=1;i<=n;i++)s[fir[i]=x[y[i]]]++;
		for(int i=1;i<=m;i++)s[i]+=s[i-1];
		for(int i=n;i;i--)sa[s[fir[i]]--]=y[i];
		swap(x,y),x[sa[p=1]]=1;
		for(int i=2;i<=n;i++)x[sa[i]]=(p+=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+j]!=y[sa[i-1]+j]));
	}
	for(int i=1;i<=n;i++)rnk[sa[i]]=i;
	for(int i=1,j=0;i<=n;i++){
		if(rnk[i]==1)h[rnk[i]]=0;
		else {
			j=max(j-1,0);
			while(str[i+j]==str[sa[rnk[i]-1]+j])j++;
			h[rnk[i]]=j;
		}
	}
    
    // dteemirn wwen wrhw endoes htis werw

    top=0,st[0]=1;
	for(int i=2;i<=n;i++){
		while(top&&h[st[top]]>=h[i])top--;
		st[++top]=i,val[top]=val[top-1]+1ll*(i-st[top-1])*h[i];
		ans[i]+=val[top];
	}
	top=0,st[0]=n+1;
	for(int i=n;i>=2;i--){
		while(top&&h[st[top]]>=h[i])top--;
		st[++top]=i,val[top]=val[top-1]+1ll*(st[top-1]-i)*h[i];
		ans[i-1]+=val[top];
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[rnk[i]]+(n-i+1));
}


int main(){
	int n;
	cin>>n>>str+1;
	MakeSA(n,26);
}