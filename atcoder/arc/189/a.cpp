#include <bits/stdc++.h>
using namespace std;


int main() {
	int n;
	long long s,ans;

	cin>>n;
	vector<long long>a(n),d[2];
	for(int i=0;i<n;i++)cin>>a[i];

	for(int i=0;i<n-1;i++)d[i%2].push_back(a[i+1]-a[i]);
	for(int i=0;i<2;i++)sort(d[i].begin(),d[i].end());

	s=a[0],ans=a[0];
	for(int i=0;i<n-1;i++){
		s+=d[i%2][i/2];
		ans+=s;
	}
	cout<<ans<<endl;
	return 0;
}
 
 // balls an boxes wer

// possbile wtates w