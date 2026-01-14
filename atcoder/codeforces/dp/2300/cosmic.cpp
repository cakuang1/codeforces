#include <bits/stdc++.h>
#define N 1000011
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second
using namespace std;
int t, n, b[N];
ll a[N];
pii s[N];
int sn;
int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 1; i <= n; ++i)
            scanf("%lld%d", a + i, b + i);

        sn = 0;
        ll x = 0;

        for (int i = 1; i <= n; ++i) {
            ll mx = 0;

            while (sn) {
                if (s[sn].s2 == b[i])
                    a[i] += s[sn--].s1 - mx;
                else if (s[sn].s1 <= a[i])
                    mx = max(mx, s[sn--].s1);
                else
                    break;
            }

            ++sn;
            s[sn] = pii(a[i], b[i]);
            x = max(x, s[sn].s1);
            printf("%lld ", x);
        }

        putchar(10);
    }

    return 0;
}