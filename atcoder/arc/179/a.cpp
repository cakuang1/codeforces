#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;
    cin >> N >> K;

    vector<ll> A(N);
    for (ll &x : A) cin >> x;

    if (K > 0) {
        sort(A.begin(), A.end());
    } else {
        sort(A.rbegin(), A.rend());
    }

    ll sum = 0;

    // Once we see a prefix sum >= K,
    // we are never allowed to see < K afterward.
    bool reached = (0 >= K);

    bool ok = true;

    for (ll x : A) {
        sum += x;

        if (sum >= K) {
            reached = true;
        } else {
            if (reached) {
                ok = false;
                break;
            }
        }
    }

    if (!ok) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << '\n';

    return 0;
}