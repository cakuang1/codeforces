#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int add(int x, int y)
{
    x += y;
    while(x >= MOD)
        x -= MOD;
    while(x < 0)
        x += MOD;
    return x;
}

int mul(int x, int y)
{
    return (x * 1ll * y) % MOD;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
        
    int ans = 0;
    vector<int> pw2(1, 1);
    while(pw2.size() < n)
        pw2.push_back(mul(pw2.back(), 2));
    int cur = mul(pw2[n - 1], a[0]);
    for(int i = 0; i < n; i++)
    {
        ans = add(ans, cur);
        if(i < n - 1)
        {
            cur = add(cur, -mul(pw2[n - 2 - i], a[i]));
            cur = add(cur, mul(pw2[n - 2 - i], a[i + 1]));
        }
    }
    printf("%d\n", ans);
} 