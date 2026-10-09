#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using S = pair<int, int>;
S op_max(S a, S b) { return a.first > b.first ? a : b; }
S e_max() { return {-1, -1}; }
S op_min(S a, S b) { return a.first < b.first ? a : b; }
S e_min() { return {INT_MAX, -1}; }
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, M;
	cin >> N >> M;
	vector<int> P(N);
	for (int &x : P) cin >> x;
	vector<S> A(N);
	for (int i = 0; i < N; i++) A[i] = {P[i], i};
	atcoder::segtree<S, op_max, e_max> seg_max(A);
	atcoder::segtree<S, op_min, e_min> seg_min(A);
	while (M--) {
		int L, R;
		cin >> L >> R;
		L--;
		const auto [mx, i] = seg_max.prod(L, R);
		const auto [mn, j] = seg_min.prod(L, R);
		swap(P[i], P[j]);
		seg_max.set(i, {P[i], i});
		seg_max.set(j, {P[j], j});
		seg_min.set(i, {P[i], i});
		seg_min.set(j, {P[j], j});
	}
	for (int i = 0; i < N; i++) {
		cout << P[i] << " \n"[i + 1 == N];
	}
}
