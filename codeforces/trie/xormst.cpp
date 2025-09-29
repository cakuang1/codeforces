#include <iostream>
#define maxn 200010
#define INF (1 << 30)
#define ll long long
using namespace std;

const int N = 30;
#define lc T[i].ch[0]
#define rc T[i].ch[1]
struct Trie {
    int ch[2]; 
} T[maxn * 30]; int rt, top;
void init_Trie() {
    for (int i = 1; i <= top; ++i) lc = rc = 0;
    rt = top = 1; 
}

void ins(int &i, int k, int o) {
    if (!i) i = ++top; 
    if (o == -1) return ;
    ins(T[i].ch[k >> o & 1], k, o - 1);
}

int query(int i, int k, int o) {
    if (o == -1) return 0; int d = k >> o & 1;
    if (T[i].ch[d]) return query(T[i].ch[d], k, o - 1);
    else return (1 << o) + query(T[i].ch[d ^ 1], k, o - 1); 
}

// wfollwos that inter edgesin eiet wew hwerv0 or b1 wewill webe have b wertuerne of we
// 
int n, a[maxn], b[maxn], c[maxn]; ll ans; 


void solve(int l, int r, int o) {
    if (o == -1 || l > r) return ;
    int c1 = 0, c2 = 0, m = l + r >> 1, v = INF;
    for (int i = l; i <= r; ++i)
        if (!(a[i] >> o & 1)) b[++c1] = a[i];
        else c[++c2] = a[i];
    init_Trie(); 
    for (int i = 1; i <= c1; ++i) ins(rt, b[i], N);
    for (int i = 1; i <= c2; ++i) v = min(v, query(rt, c[i], N));
    for (int i = 1; i <= c1; ++i) a[l + i - 1] = b[i];
    for (int i = 1; i <= c2; ++i) a[l + c1 + i - 1] = c[i];
    if (c1 && c2) ans += v;
    solve(l, l + c1 - 1, o - 1); solve(l + c1, r, o - 1); 
}

int main() { 
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    solve(1, n, N); cout << ans << "\n";
    return 0; 
} 