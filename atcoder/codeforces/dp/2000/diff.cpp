#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int add(int x, int y)
{
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}   

const int ZERO = 100000;

int dp[2][ZERO * 2];

void recalc(int x)
{
    for(int i = 0; i < ZERO * 2; i++)
        dp[1][i] = 0;

    for(int i = 0; i < ZERO * 2; i++)
    {
        if(dp[0][i] == 0) continue;
        int nx = x + i;
        dp[1][nx] = add(dp[1][nx], dp[0][i]);
        if(nx != ZERO)
            dp[1][2 * ZERO - nx] = add(dp[1][2 * ZERO - nx], dp[0][i]);
    }

    for(int i = 0; i < ZERO * 2; i++)
        dp[0][i] = dp[1][i];
}


int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    dp[0][ZERO] = 1;
    for(int i = 1; i + 1 < n; i++)
        recalc(a[i]);
    int ans = 0;
    for(int i = 0; i < ZERO * 2; i++)
        ans = add(ans, dp[0][i]);
    cout << ans << endl;
}