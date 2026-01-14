#include<bits/stdc++.h>
using namespace std;


#define all(v)         v.begin(),v.end()
#define endl           "\n"


int solve(){
 		int n; cin >> n;
 		string s; cin >> s;
 		auto cnt = count(all(s),'1');
 		if(cnt == 0 or cnt & 1){
 			cout << "NO" << endl;
 			return 0;
 		}
 		auto inc = [&](int j){
		 	return (j + 1)%n;
		};
 		cout << "YES" << endl;
 		for(int p = 1; p < n; p++){
 			if(s[p - 1] == '1'){
		 		auto i = inc(p);
		 		while(i != p){
		 			int j = i;
		 			int prev = p;
		 			while(j != p){
		 				cout << prev + 1 << " " << j + 1 << endl;
		 				prev = j;
		 				j = inc(j);
		 				if(s[prev] == '1')break;
		 			}
		 			i = j;
		 		}
		 		return 0;
 			}
 		}

 return 0;
}
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    #ifdef SIEVE
    sieve();
    #endif
    #ifdef NCR
    init();
    #endif
    int t=1;cin>>t;
    while(t--){
        solve();
    }
    return 0;
}