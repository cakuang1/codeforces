#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif

	int tt = clock();
	
	string s;
	cin >> s;
	
	vector<int> dp(1 << 20);
	vector<int> masks;
	for (int i = 0; i < int(s.size()); ++i) {
		vector<bool> used(20);
		int mask = 0;
		for (int j = 0; i + j < int(s.size()); ++j) {
			if (used[s[i + j] - 'a']) break;
			used[s[i + j] - 'a'] = true;
			mask |= 1 << (s[i + j] - 'a');
			masks.push_back(mask);
		}
	}
	sort(masks.begin(), masks.end());
	masks.resize(unique(masks.begin(), masks.end()) - masks.begin());
	sort(masks.begin(), masks.end(), [](int x, int y){
		return __builtin_popcount(x) > __builtin_popcount(y);
	});
	
	int ans = __builtin_popcount(masks[0]);
	for (int i = 0; i < int(masks.size()); ++i) {
		if (clock() - tt > 1900) {
			break;
		}
		for (int j = i + 1; j < int(masks.size()); ++j) {
			if (!(masks[i] & masks[j])) {
				ans = max(ans, __builtin_popcount(masks[i]) + __builtin_popcount(masks[j]));
				break;
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
} 