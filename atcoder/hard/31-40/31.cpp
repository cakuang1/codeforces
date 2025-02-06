#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <stdio.h>
using namespace std;
#define int long long
int MOD = 1000000007;
signed main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}

	vector<int> X(N + 1, 0);
	vector<int> res;
	for (int i = N; i > 0; i--) {
		int cnt = 0;
		for (int j = i; j <= N; j += i) {
			cnt ^= X[j];
		}
		if (cnt != A[i]) {
			X[i] = 1;
			res.push_back(i);
		}
	}
	cout << res.size() << endl;
	for (int i = 0; i < res.size(); i++) {
		if (i > 0)cout << " ";
		cout << res[i];
	}
	cout << endl;
}