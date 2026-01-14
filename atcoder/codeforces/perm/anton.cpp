//雪花飄飄北風嘯嘯
//天地一片蒼茫

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#define ll long long
#define ii pair<ll,ll>
#define iii pair<ii,ll>
#define fi first
#define se second
#define endl '\n'
#define debug(x) cout << #x << " is " << x << endl

#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define lb lower_bound
#define ub upper_bound

#define rep(x,start,end) for(auto x=(start)-((start)>(end));x!=(end)-((start)>(end));((start)<(end)?x++:x--))
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

#define indexed_set tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>
//change less to less_equal for non distinct pbds, but erase will bug

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int n;
string s;
int cnt[4];

ll flips[4][4];

map<char,int> id={{'A',0},{'N',1},{'O',2},{'T',3}};
string cset="ANOT";

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin.exceptions(ios::badbit | ios::failbit);
	
	int TC;
	cin>>TC;
	while (TC--){
		cin>>s;
		n=sz(s);
		
		memset(cnt,0,sizeof(cnt));
		memset(flips,0,sizeof(flips));
		
		rep(x,0,n){
			cnt[id[s[x]]]++;
		}
		rep(a,0,4){
			int curr=0;
			rep(x,0,n){
				flips[a][id[s[x]]]+=curr;
				if (id[s[x]]==a) curr++;
			}
		}
		
		ll best=-1;
		vector<int> ans;
		
		vector<int> v={0,1,2,3};
		do{
			ll curr=0;
			rep(x,0,4){
				rep(y,x+1,4){
					curr+=flips[v[y]][v[x]];
				}
			}
			
			if (curr>best){
				best=curr;
				ans=v;
			}
		} while (next_permutation(all(v)));
		
		for (auto &it:ans) rep(x,0,cnt[it]) cout<<cset[it];
		cout<<endl;
	}
}