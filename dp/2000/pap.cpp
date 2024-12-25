#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#define maxn 1000010
#define pb push_back
using namespace std;

int n, m;

struct node {
    int t, x, y;
} a[maxn];

int f[maxn], ans, mx = -1;
int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].t >> a[i].x >> a[i].y;
    int k = 0; a[0].t = 0; a[0].x = a[0].y = 1; memset(f, -1, sizeof f); f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        while (a[k + 1].t + 2 * m - 2 <= a[i].t) mx = max(mx, f[k++]);
        if (~mx) f[i] = mx + 1; 
        for (int j = k; j < i; ++j)
            if (~f[j] && a[i].t - a[j].t >= abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y))
                f[i] = max(f[i], f[j] + 1);
        ans = max(ans, f[i]); 
    } cout << ans << endl;
    return 0;
} 
