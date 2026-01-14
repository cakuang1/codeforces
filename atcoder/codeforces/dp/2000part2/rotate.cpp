#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 6, M = 105;

#define LF(i, __l, __r) for (int i = __l; i <= __r; i++)
#define RF(i, __r, __l) for (int i = __r; i >= __l; i--)

struct col { int a[N], mx; } a[M];
int t, n, m, ans, mx[N];
int back[N][N][N];

bool cmp(col a, col b) { return a.mx > b.mx; }

void Init() {
    ans = 0;
    memset(mx, 0, sizeof(mx));
    memset(back, 0, sizeof(back));
    memset(a, 0, sizeof(a));
}

void dfs(int u) {
    if (u == n + 2) {
        int res = 0;
        LF(i, 1, n) res += mx[i];
        ans = max(ans, res);
        return;
    }

    LF(i, 0, n - 1) {
        LF(j, 1, n) {
            int s = i + j;
            if (s > n) s %= n;
            back[u][i][s] = mx[s];
            mx[s] = max(mx[s], a[u].a[j]);
        }
        dfs(u + 1);
        LF(j, 1, n) mx[j] = back[u][i][j];
    }
}

int main() {
    scanf("%d", &t);

    while (t--) {
        Init();
        scanf("%d%d", &n, &m);
        LF(i, 1, n) LF(j, 1, m) {
            scanf("%d", &a[j].a[i]);
            a[j].mx = max(a[j].mx, a[j].a[i]);
        }

        sort(a + 1, a + m + 1, cmp);
        
        dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}


