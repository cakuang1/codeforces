#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 4e18+10;
const int mod = 1000000007;
const int mx = 200010; //check the limits, dummy
typedef pair<int, int> pa;
const double PI = acos(-1);
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
#define swa(a,b) a^=b^=a^=b
#define re(i,a,b) for(int i=(a),_=(b);i<_;i++)
#define rb(i,a,b) for(int i=(b),_=(a);i>=_;i--)
#define clr(a) memset(a, 0, sizeof(a))
#define lowbit(x) ((x)&(x-1))
#define mkp make_pair
void sc(int& x) { scanf("%d", &x); }void sc(int64_t& x) { scanf("%lld", &x); }void sc(double& x) { scanf("%lf", &x); }void sc(char& x) { scanf(" %c", &x); }void sc(char* x) { scanf("%s", x); }
ll  m, n,y,z,k,sum=0,ans=0;
const int N = 3030,M= 998244353;
ll dp[N][N];
string s, t;
bool match(int i, char c) {
    if (i > m)return 1;
    else return t[i - 1] == c;
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> s >> t;
    n = s.size();
    m = t.size();

    for (int i = 1; i <= n + 1; i++)
        dp[i][i - 1] = 1;
    for (int d = 1; d <= n; d++)
    {
        char c = s[d - 1];
        for (int i = 1, j = d; j <= n; i++, j++)
        {
            if (match(i, c))
            {
                dp[i][j] = (dp[i][j] + dp[i + 1][j]) % M;
            }
            if (match(j, c))
            {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % M;
            }
        }
    }

    int ans = 0;
    for (int i = m; i <= n; i++)
    {
        ans = (ans + dp[1][i]) % M;
    }
    cout << ans << "\n";
    
    return 0;
}