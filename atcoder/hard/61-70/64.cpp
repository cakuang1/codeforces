#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int N, M, a[55], b[55], par[55];
int root(int x) {
	if (x == par[x]) return x;
	return par[x] = root(par[x]);
}
void unite(int x, int y) {
	x = root(x);
	y = root(y);
	par[x] = y;
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) cin >> a[i] >> b[i], a[i]--, b[i]--;
	int ret = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) par[j] = j;
		for (int j = 0; j < M; j++) {
			if (i != j) unite(a[j], b[j]);
		}
		bool f = false;
		for (int j = 1; j < N; j++) {
			if (root(j - 1) != root(j)) f = true;
		}
		if (f) ret++;
	}
	cout << ret << endl;
	return 0;
}