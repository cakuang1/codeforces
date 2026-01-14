#include <bits/stdc++.h>
#define fi first 
#define se second 
#define N 800005
using namespace std;
int n, m;
struct line {
	int l, r;
};
vector<line> b[N];
struct SegmentTree {
	int p, l, r;
	int dp;//区间最大值
	int id;//这个最大值对应的行号 便于输出
	int tag1, tag2;
} t[N * 4];
int root, tot;
void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	t[p].tag1 = t[p].tag2 = -1;
	if(l == r) {
		t[p].dp = t[p].id = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(2 * p, l, mid);
	build(2 * p + 1, mid + 1, r);
	t[p].dp = t[p].id = 0;
	return;
}
void spread(int p) {
	if(t[p].tag1 != -1) {
		t[2 * p].dp = t[p].tag1;
		t[2 * p].tag1 = t[p].tag1;
		t[2 * p].id = t[p].tag2;
		t[2 * p].tag2 = t[p].tag2;
		t[2 * p + 1].dp = t[p].tag1;
		t[2 * p + 1].tag1 = t[p].tag1;
		t[2 * p + 1].id = t[p].tag2;
		t[2 * p + 1].tag2 = t[p].tag2;
		t[p].tag1 = t[p].tag2 = -1;
	}
}
pair<int, int> query(int p, int L, int R) {
 	if(t[p].l >= L && t[p].r <= R) {
		return make_pair(t[p].dp, t[p].id);
	}
	spread(p);
	int mid = (t[p].l + t[p].r) >> 1;
	int mx = 0, id = 0;
	pair<int, int> ret = {0, 0};
	if(L <= mid) ret = query(2 * p, L, R);
	if(R > mid) {
		pair<int, int> tmp = query(2 * p + 1, L, R);
		if(tmp.fi > ret.fi) {
			ret.fi = tmp.fi;
			ret.se = tmp.se;
		}
	}
	return ret;
}
void modify(int p, int L, int R, int v, int id) {
	if(t[p].l >= L && t[p].r <= R) {//注意 不论v是否大于t[p].dp 都要进行更新
		t[p].dp = v;
		t[p].id = id;
		t[p].tag1 = v;
		t[p].tag2 = id;
		return;
	}
	spread(p);
 
	int mid = (t[p].l + t[p].r) >> 1;
	if(L <= mid) modify(2 * p, L, R, v, id);
	if(R > mid) modify(2 * p + 1, L, R, v, id);
	t[p].dp = max(t[2 * p].dp, t[2 * p + 1].dp);
	if(t[2 * p + 1].dp > t[2 * p].dp) {
		t[p].dp = t[2 * p + 1].dp;
		t[p].id = t[2 * p + 1].id;
	} else {
		t[p].dp = t[2 * p].dp;
		t[p].id = t[2 * p].id;
	}
}
int pre[N];
bool vis[N];
int ans = 0, last = 0;
int main() {
	cin >> n >> m;
	vector<int> v;
	for(int i = 1; i <= m; i++) {
		int row, l, r;
		scanf("%d%d%d", &row, &l, &r);
		v.push_back(l);
		v.push_back(r);
		b[row].push_back({l, r});
	}
	sort(v.begin(), v.end());
	vector<int>::iterator it = unique(v.begin(), v.end());
	v.erase(it, v.end());
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < b[i].size(); j++) {
			b[i][j].l = lower_bound(v.begin(), v.end(), b[i][j].l) - v.begin() + 1;
			b[i][j].r = lower_bound(v.begin(), v.end(), b[i][j].r) - v.begin() + 1;
		}
	}
	
	build(1, 1, v.size());
	for(int i = 1; i <= n; i++) {
		int mx_result = 0, pre_row = 0;
		for(int j = 0; j < b[i].size(); j++) {
			pair<int, int> tmp = query(1, b[i][j].l, b[i][j].r);
			if(tmp.fi > mx_result) {
				mx_result = tmp.fi;
				pre_row = tmp.se;
			}
		}
 
		int dp = mx_result + 1;
		pre[i] = pre_row;
		if(dp > ans) {
			ans = dp;
			last = i;
		}
		for(int j = 0; j < b[i].size(); j++) {
			modify(1, b[i][j].l, b[i][j].r, dp, i);
		}
	}
	cout << n - ans << '\n';
	int now = last;
	vis[now] = 1;
	while(pre[now]) {
		now = pre[now];
		vis[now] = 1;
	}
	vector<int> aa;
	int fk = 0;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) cout << i << " ";
	}
	return 0;


}


// does thiwe