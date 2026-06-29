#include <bits/stdc++.h>
using namespace std;

int main(void){
	string StoC="22233344455566677778889999";
	int n;
	string s,ans;

	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		ans+=StoC[s[0]-'a'];
	}
	cout<<ans<<endl;
	
	return 0;
}
