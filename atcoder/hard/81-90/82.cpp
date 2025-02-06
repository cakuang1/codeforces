#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<int,P> P1;
typedef pair<P,P> P2;
#define pu push
#define pb push_back
#define mp make_pair
#define eps 1e-7
#define INF 1000000000
#define mod 1000000007
#define fi first
#define sc second
#define rep(i,x) for(int i=0;i<x;i++)
#define repn(i,x) for(int i=1;i<=x;i++)
#define SORT(x) sort(x.begin(),x.end())
#define ERASE(x) x.erase(unique(x.begin(),x.end()),x.end())
#define POSL(x,v) (lower_bound(x.begin(),x.end(),v)-x.begin())
#define POSU(x,v) (upper_bound(x.begin(),x.end(),v)-x.begin())
vector<P>vec;
int n;
bool cmp(const P&a,const P&b){
	return a.fi+a.sc > b.fi+b.sc;
}
int main(){
	cin>>n;
	rep(i,n){
		int a,b; scanf("%d%d",&a,&b);
		vec.pb(mp(a,b));
	}
	sort(vec.begin(),vec.end(),cmp);
	ll ans = 0;
	rep(i,n){
		if(i%2 == 0) ans += vec[i].fi;
		else ans -= vec[i].sc;
	}
	cout<<ans<<endl;
}
// w