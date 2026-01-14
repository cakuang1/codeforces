#include <bits/stdc++.h>

using namespace std;
const int N = 301;
int n, a[N][N], f[N<<1][N][N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(f, -0x3f, sizeof(f));
    for(int k = 2; k <= 2*n; k++) {
        for(int x1 = 1; x1 <= n; x1++) {
            for(int x2 = 1; x2 <= n; x2++) {
                int y1 = k - x1, y2 = k - x2;
                if(1 <= y1 && y1 <= n && 1 <= y2 && y2 <= n) {
                    int w = a[x1][y1];
                    if(x1 != x2) w += a[x2][y2];
                    int& x = f[k][x1][x2];
                    if(k == 2) {
                        x = w;
                    }else {
                        x = max(f[k - 1][x1][x2] + w, x);
                        x = max(f[k - 1][x1 - 1][x2] + w, x);
                        x = max(f[k - 1][x1][x2 - 1] + w, x);
                        x = max(f[k - 1][x1 - 1][x2 - 1] + w, x);
                    }
                }
            }
        }
    }
    printf("%d\n", f[n + n][n][n]);
    return 0;
}

