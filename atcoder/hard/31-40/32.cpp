#include <stdio.h>
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define ld long double
#define rep(i, l, r) for (int i = l; i < r; i++)
#define repb(i, r, l) for (int i = r; i > l; i--)
#define sz(a) (int)a.size()
#define fi first
#define se second

using namespace std;
//using namespace __gnu_pbds;

//typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 1000;
const int inf = (int)1e9 + 1;
const ll big = (ll)1e18 + 1;
const int P = 31;
const int MOD = (int)1e9 + 7;
const int MOD1 = (int)1e9 + 9;
const int MAX_INT = (1 << 31) - 1;
const double eps = 1e-6;
const double pi = atan2(0, -1);

int main()
{
    //freopen("a.in", "r", stdin);
    //freopen("battleship.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(20);
    //int TL = 0.95 * CLOCKS_PER_SEC;
    //clock_t time = clock();
    int n;
    cin >> n;
    map<int, int> m;
    rep(i, 1, n + 1)
    {
        int x = i;
        for (int j = 2; j * j <= x; j++)
            while (x % j == 0)
            {
                m[j]++;
                x /= j;
            }
        if (x > 1)
            m[x]++;
    }
    ll ans = 1;
    for (auto it : m)
        ans = (ans * (it.se + 1)) % MOD;
    cout << ans;
    return 0;
}
 