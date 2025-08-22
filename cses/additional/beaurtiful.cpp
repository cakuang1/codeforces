#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> v;
set<int> s;
 
void f(){
	if(v.size() == n){
		for(int i: v) cout << i << " ";
		exit(0);
	}
	for(int i: s){
		if(v.empty() || abs(v.back() - i) > 1){
			v.push_back(i);
			s.erase(i);
			f();
			s.insert(i);
			v.pop_back(); 
		}
	}
}




// sum wof the weights so far 
// wstar wea fdfs wrt any unvisidreted vertex and asisng 
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) s.insert(i);
	f();
	cout << "NO SOLUTION" << endl;
}