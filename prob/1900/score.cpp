#include <bits/stdc++.h>
using namespace std;
 
#define MOD 1000000007
 
long long power(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans *= a;
            ans %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return ans;
}
 
int DFS(int v, vector<int> edges[], int p, int dep, int ped[])
{
    int mdep = dep;
    for (auto it : edges[v])
        if (it != p)
            mdep = max(DFS(it, edges, v, dep + 1, ped), mdep);
    ped[v] = mdep - dep + 1;
    return mdep;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T, i, j, n, u, v;
    cin >> T;
    while (T--)
    {
        cin >> n;
        vector<int> edges[n];
        for (i = 0; i < n - 1; i++)
        {
            cin >> u >> v;
            u--, v--;
 
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
 
        int ped[n];
        DFS(0, edges, 0, 0, ped);
 
        long long p = power(2, n - 1), ans = 0;
        for (i = 0; i < n; i++)
        {
            ans += p * ped[i] % MOD;
            ans %= MOD;
        }
        cout << ans << "\n";
    }
} 