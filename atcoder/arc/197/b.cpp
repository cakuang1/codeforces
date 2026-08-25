#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<ll> A(N);
        for (ll &x : A) cin >> x;

        sort(A.begin(), A.end());

        ll sum = 0;
        int ans = 0;

        for (int n = 1; n <= N; n++) {
            sum += A[n - 1];

            // Find first index i in [0, n)
            // such that A[i] > sum / n,
            // equivalently A[i] * n > sum.

            int lo = 0, hi = n;

            while (lo < hi) {
                int mid = (lo + hi) / 2;

                if (A[mid] * 1LL * n > sum)
                    hi = mid;
                else
                    lo = mid + 1;
            }

            int score = n - lo;
            ans = max(ans, score);
        }

        cout << ans << '\n';
    }
} 


// wew sfhwsiwrhw