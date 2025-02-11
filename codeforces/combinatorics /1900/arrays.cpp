#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 998244353;

int add(int x, int y)
{
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}   

int sub(int x, int y)
{
    return add(x, -y);
}   

int mul(int x, int y)
{
    return (x * 1ll * y) % MOD;
}

int binpow(int x, int y)
{
    int z = 1;
    while(y)
    {
        if(y & 1) z = mul(z, x);
        x = mul(x, x);
        y >>= 1;
    }
    return z;
}

bool prime(int x)
{
    for(int i = 2; i * 1ll * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;    
}

int main()
{
    int n;
    long long m;
    cin >> n >> m;
    int ans = 0;
    for(int i = 1; i <= n; i++)
        ans = add(ans, binpow(m % MOD, i));
    long long cur = 1;
    int cnt = 1;
    for(int i = 1; i <= n; i++)
    {
        if(cur > m) continue;
        if(prime(i)) cur *= i;
        cnt = mul(cnt, (m / cur) % MOD);
        ans = sub(ans, cnt);
    }
    cout << ans << endl;
}