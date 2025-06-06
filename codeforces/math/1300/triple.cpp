
#include <bits/stdc++.h>

using namespace std;

const int MAX = 200'007;
const int MOD = 1'000'000'007;

int a[MAX], psum[MAX];

int f(int x) {
	int cnt = 0;
	while (x) {
		x /= 3;
		cnt++;
	}
	return cnt;
}

void solve() {
	int l, r;
	cin >> l >> r;
	cout << psum[r] - psum[l - 1] + a[l] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	psum[0] = 0;
	for (int i = 1; i < MAX - 1; i++) {
		a[i] = f(i);
		psum[i] = psum[i - 1] + a[i];
	}
	
	int tt; cin >> tt; for (int i = 1; i <= tt; i++) {solve();}
	// solve();
}

