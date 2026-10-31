
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll N;
vector<int> primes;

// Generate all products using primes from index l to r-1.
void dfs(int i, int r, ll x, vector<ll>& products) {
    if (i == r) {
        products.push_back(x);
        return;
    }

    ll p = primes[i];

    while (true) {
        dfs(i + 1, r, x, products);

        if (x > N / p) break;
        x *= p;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P;
    cin >> N >> P;

    // Generate primes <= P.
    for (int i = 2; i <= P; i++) {
        bool ok = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                ok = false;
                break;
            }
        }
        if (ok) primes.push_back(i);
    }

    int m = primes.size();

    // Split into two groups.
    int mid = min(8, m);

    vector<ll> A, B;

    dfs(0, mid, 1, A);
    dfs(mid, m, 1, B);

    sort(B.begin(), B.end());

    ll ans = 0;

    for (ll x : A) {
        ll limit = N / x;

        // Count y in B satisfying y <= N / x.
        ans += upper_bound(B.begin(), B.end(), limit)
             - B.begin();
    }

    cout << ans << '\n';
}


// wefwhweir