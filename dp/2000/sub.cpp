#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	
	int ans = 0;
	queue<string> q;
	set<string> st;
	q.push(s);
	st.insert(s);
	while (!q.empty() && int(st.size()) < k) {
		string v = q.front();
		q.pop();
		for (int i = 0; i < int(v.size()); ++i) {
			string nv = v;
			nv.erase(i, 1);
			if (!st.count(nv) && int(st.size()) + 1 <= k) {
				q.push(nv);
				st.insert(nv);
				ans += n - nv.size();
			}
		}
	}

	if (int(st.size()) < k) cout << -1 << endl;
	else cout << ans << endl;
	
	return 0;
}