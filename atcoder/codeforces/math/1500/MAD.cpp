#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX = 200'007;
const int MOD = 1'000'000'007;
 
void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> v;
	while (n) {
		v.push_back((n + 1) / 2);
		n /= 2;
	}
	int tot = 0, pow2 = 1;
	for (int x : v) {
		if (tot < k && k <= tot + x) {
			cout << pow2 * (2 * (k - tot) - 1) << '\n';
			return;
		}
		tot += x;
		pow2 *= 2;
	}
}
 
int main() {
	int tt; cin >> tt; for (int i = 1; i <= tt; i++) {solve();}
	// solve();
}