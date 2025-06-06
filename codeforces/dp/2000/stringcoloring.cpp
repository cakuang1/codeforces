#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	int n;
	string s;
	cin >> n >> s;
	
	vector<int> maxdp(26);
	vector<int> dp(n, 1);
	for (int i = 0; i < n; ++i) {
		for (int c = 25; c > s[i] - 'a'; --c) {
			dp[i] = max(dp[i], maxdp[c] + 1);
		}
		maxdp[s[i] - 'a'] =  max(maxdp[s[i] - 'a'], dp[i]);
	}
	
	cout << *max_element(maxdp.begin(), maxdp.end()) << endl;
	for (int i = 0; i < n; ++i) cout << dp[i] << " ";
	cout << endl;
	
	return 0;
}