#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
	int X = *max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end());
	int Y = *max_element(y.begin(), y.end()) - *min_element(y.begin(), y.end());
	int ans = (max(X, Y) + 1) / 2;
	cout << ans << '\n';
}
