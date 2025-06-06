#include <bits/stdc++.h>
using namespace std;

int main(void){
	int n,k;
	long long a,y=1,x=1;

	cin>>n>>k;

	for(int i=0;i<k;i++)y*=10;
	y--;

	for(int i=0;i<n;i++){
		cin>>a;
		if(x>(y/a))x=1;
		else x*=a;
	}
	cout<<x<<endl;
	return 0;
}




//