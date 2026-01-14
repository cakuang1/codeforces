#include <iostream>
#include <cstdio>
#define maxn 100010
using namespace std;

int n, a[maxn];

int vis[maxn];

#define lc T[i].ch[0]
#define rc T[i].ch[1]
#define Lc T[j].ch[0]
#define Rc T[j].ch[1]
struct zhuxi {
    int v, ch[2]; 
} T[maxn * 40]; int top, rt[maxn];
void update(int &i, int j, int l, int r, int k, int v) {
    i = ++top; T[i] = T[j]; T[i].v += v; 
    if (l == r) return ; int m = l + r >> 1;
    if (k <= m) update(lc, Lc, l, m, k, v);
    else update(rc, Rc, m + 1, r, k, v); 
}

int query(int i, int l, int r, int k) {
    if (l == r) return k >= T[i].v ? l : 0;
    int m = l + r >> 1;
    if (k < T[lc].v) return query(lc, l, m, k);
    else if (k > T[lc].v) return query(rc, m + 1, r, k - T[lc].v);
    else return max(m, query(rc, m + 1, r, 0)); 
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n; 
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i; --i) {
        rt[i] = rt[i + 1]; 
        if (vis[a[i]]) update(rt[i], rt[i], 1, n, vis[a[i]], -1);
        vis[a[i]] = i; 
        update(rt[i], rt[i], 1, n, vis[a[i]], 1); 
    } 
    for (int k = 1; k <= n; ++k) {
        int p = 1, ans = 0;  
        while (p <= n) {
            p = query(rt[p], 1, n, k) + 1;
            ++ans;
        }
        cout << ans << " ";
    } 
    return 0;
} 