#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
	int n;
	cin >> n;

	vector<ll> L(n), R(n);
	for(int i = 0; i < n; i++) cin >> L[i] >> R[i];

	vector<ll> l(n), r(n);
	l.back() = L.back(), r.back() = R.back();

	for(int i = n - 2; i >= 0; i--) {
		if(R[i] < l[i + 1]) {
			l[i] = r[i] = R[i];
		} else if(L[i] > r[i + 1]) {
			l[i] = r[i] = L[i];
		} else {
			l[i] = max(L[i], l[i + 1]);
			r[i] = min(R[i], r[i + 1]);
		}
	}

	vector<ll> a(n);
	a.front() = l.front();

	for(int i = 1; i < n; i++) { a[i] = clamp(a[i - 1], L[i], r[i]); }
	for(int i = 0; i < n; i++) { cout << a[i] << (i == n - 1 ? '\n' : ' '); }
}
