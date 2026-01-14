#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int a[N];
int f[N][N];
int dp[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i][i] = a[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int j = l; j < r; j++) {
                if (f[l][j] && f[l][j] == f[j + 1][r])
                    f[l][r] = f[l][j] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = 1e7;
        for (int j = 0; j < i; j++)
            if (f[j + 1][i]) dp[i] = min(dp[i], dp[j] + 1);
    }

    cout << dp[n] << endl;
}

// subset of k determine roundness how knapsack? w w