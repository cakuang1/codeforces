#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	int n = s.size();
	vector<char> t(n);
	for (int i = 0; i < n; i++) {
		if (s[i] == '#') {
			cout << '#';
		} else if (i == 0 || s[i - 1] == '#') {
			cout << 'o';
		} else {
			cout << '.';
		}
	}
	cout << endl;
	return 0;
}
