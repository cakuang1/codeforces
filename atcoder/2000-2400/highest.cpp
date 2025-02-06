#include <bits/stdc++.h>

using namespace std;

int main(void){
	int n;
	long double x,y;
	cin>>n;
	vector<long double>a(n+1,0.0);
	vector<long double>ans(n);
	vector<int>b;
	for(int i=0;i<n;i++){
		cin>>a[i+1];
		a[i+1]+=a[i];
	}
	int bsz=0;
	for(int i=n;i>=0;i--){
		while(b.size()>1){
			x=(a[b[bsz-1]]-a[i])*((long double)(b[bsz-2]-i));
			y=(a[b[bsz-2]]-a[i])*((long double)(b[bsz-1]-i));
			if(x<=y){
				b.pop_back();
				bsz--;
			}
			else break;
		}
		if(i<n)ans[i]=(a[b[bsz-1]]-a[i])/((long double)(b[bsz-1]-i));
		b.push_back(i);
		bsz++;
	}
	for(int i=0;i<n;i++)cout<< std::fixed << std::setprecision(10)<<ans[i]<<endl;
	return 0;
}
