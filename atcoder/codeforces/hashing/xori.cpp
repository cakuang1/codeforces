#include <bits/stdc++.h>

using namespace std;

typedef pair<long long, long long> pt;

const int N = int(3e5) + 99;
const pt zero = make_pair(0, 0);

int n;
int a[N];
pt hsh[N], sumHsh[N];

void upd(pt &a, pt b){
    a.first ^= b.first;
    a.second ^= b.second;
}

int calc(int pos){
	set <int> sl, sr;
	set<pt> s;
	int r = pos + 1, l = pos - 1;
	pt curr = hsh[0], curl = zero;
	s.insert(zero);
	sr.insert(0), sl.insert(0);
	
	int res = 0;	
	while(r < n && !sr.count(a[r])){
		sr.insert(a[r]);
		upd(curr, hsh[a[r]]);
		++r;

		while(l >= 0 && !sl.count(a[l]) && a[l] < *sr.rbegin()){
			sl.insert(a[l]);
			upd(curl, hsh[a[l]]);
			s.insert(curl);
			--l;	
		}

		pt need = sumHsh[*sr.rbegin()];
		upd(need, curr);
		if(s.count(need)) ++res;
	}	

	return res;
}	







int main() {
    long long x = 0;
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		--a[i];	
		x ^= a[i];
	}
    / /w
    mt19937_64 rnd(time(NULL));
	for(int i = 0; i < N; ++i){
		hsh[i].first = rnd() ^ x;
		hsh[i].second = rnd() ^ x;
		sumHsh[i] = hsh[i];
		if(i > 0) upd(sumHsh[i], sumHsh[i - 1]);
	}
	
	int res = 0;
		
	for(int tc = 0; tc < 2; ++tc){
		for(int i = 0; i < n; ++i)
			if(a[i] == 0)
				res += calc(i) + (tc == 0);
		reverse(a, a + n);
	}
	cout << res << endl;

	return 0;
} 