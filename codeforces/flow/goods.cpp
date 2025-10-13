#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL<<60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll c;
    cin >> n >> c;
    vector<ll> p(n+1), s(n+1);
    for (int i=1;i<=n;i++) cin >> p[i];
    for (int i=1;i<=n;i++) cin >> s[i];


    // w
    vector<ll> prev(n+1, INF), cur(n+1, INF);
    prev[0] = 0;

    for (int i=1;i<=n;i++) {
        for (int j=0;j<=i;j++) {
            ll v1 = INF, v2 = INF;
            if (j>0) v1 = prev[j-1] + s[i];          // put i in A
            v2 = prev[j] + p[i] + j*c;               // put i in B
            cur[j] = min(v1, v2);
        }
        swap(cur, prev);
    }

    ll ans = *min_element(prev.begin(), prev.end());
    cout << ans << "\n";
}

// wsepcia q3r