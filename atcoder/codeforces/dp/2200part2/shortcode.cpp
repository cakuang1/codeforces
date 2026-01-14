#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define maxn 100010
#define ll long long 
using namespace std;

int n, m;

char s[maxn];

#define ch s[i] - 'a'
struct Trie {
    int nxt[26], v;
} T[maxn]; int top = 1, rt = 1;
void insert(char *s) {
    int l = strlen(s), now = rt;
    for (int i = 0; i < l; ++i) {
        if (!T[now].nxt[ch]) T[now].nxt[ch] = ++top;
        now = T[now].nxt[ch];
    } ++T[now].v;
}
#undef ch

priority_queue<int> Q[maxn]; int Rt[maxn];
inline int merge(int u, int v) {
    if (!u || !v) return u + v; 
    if (Q[u].size() > Q[v].size()) swap(u, v);
    while (!Q[v].empty()) Q[u].push(Q[v].top()), Q[v].pop();
    return u;
}

ll ans; int dep[maxn]; 
void dfs(int u) {
    if (T[u].v) {
        Rt[u] = u; 
        Q[Rt[u]].push(dep[u]); 
    }
    for (int ch = 0; ch < 26; ++ch) {
        int v = T[u].nxt[ch]; if (!v) continue;
        dep[v] = dep[u] + 1; dfs(v);
        Rt[u] = merge(Rt[u], Rt[v]); 
    }
    if (u != rt && !Q[Rt[u]].empty() && !T[u].v) {
        Q[Rt[u]].pop();
        Q[Rt[u]].push(dep[u]); 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s, insert(s);
    dfs(rt); ll sum = 0;
    while (!Q[Rt[rt]].empty()) sum += Q[Rt[rt]].top(), Q[Rt[rt]].pop();
    cout << sum << "\n"; 
    return 0;
} 

