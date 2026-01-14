#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int n;
ll a, b;
vector<int> arr;
set<int> primes;

void findPrimes(int val) {
    for (int i = -1; i <= 1; i++) {
        int x = val + i;
        int temp = x;
        for (int j = 2; j * j <= temp; j++) {
            if (x % j == 0) {
                primes.insert(j);
                while (x % j == 0) x /= j;
            }
        }
        if (x > 1) primes.insert(x);
    }
}

ll solve(int prime) {
    vector<vector<ll>> dp(n + 1, vector<ll>(3, INF));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        ll val = arr[i];

        // Transition to start or continue deletion
        dp[i + 1][1] = min(dp[i][0], dp[i][1]) + a;

        // Option 1: divisible by prime
        if (val % prime == 0) {
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][0]);
            dp[i + 1][2] = min(dp[i + 1][2], min(dp[i][1], dp[i][2]));
        }
        // Option 2: fixable with +1 or -1
        else if ((val + 1) % prime == 0 || (val - 1) % prime == 0) {
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][0] + b);
            dp[i + 1][2] = min(dp[i + 1][2], min(dp[i][1], dp[i][2]) + b);
        }
        // Option 3: cannot fix, must be deleted — nothing added to dp[i+1][0] or [2]
    }

    return min({dp[n][0], dp[n][1], dp[n][2]});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    findPrimes(arr[0]);
    findPrimes(arr[n - 1]);

    ll res = INF;
    for (int p : primes) {
        res = min(res, solve(p));
    }

    cout << res << '\n';
    return 0;
}
