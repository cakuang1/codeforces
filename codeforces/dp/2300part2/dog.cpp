#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define maxn 200010
using namespace std;

int n;

struct Edge {
    int to, next;
} e[maxn * 2]; int c1, head[maxn];
inline void add_edge(int u, int v) {
    e[c1].to = v; e[c1].next = head[u]; head[u] = c1++;
}

int f[maxn], dep[maxn], ans;
void dfs(int u, int fa) {
    vector<int> a; 
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to; if (v == fa) continue;
        dep[v] = dep[u] + 1; dfs(v, u);
        a.push_back(f[v]);
    }
    if (a.empty()) return (void) (f[u] = dep[u]);
    if (u != 1) {
        if (a.size() > 1) ans = max(*max_element(a.begin(), a.end()) - dep[u] + 1, ans);
        f[u] = *min_element(a.begin(), a.end());
    }
    else {
        sort(a.begin(), a.end());
        ans = max({ans, a.back() - dep[u], a.size() > 1 ? a[a.size() - 2] - dep[u] + 1 : 0});
    }
}

void work() { fill(head, head + maxn, -1);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        add_edge(x, y); add_edge(y, x);
    } ans = 0; dep[1] = 1; dfs(1, 0); cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) work(); 
    return 0;
} 