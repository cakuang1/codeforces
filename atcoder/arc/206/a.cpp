#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int &x : A) cin >> x;

    // cnt[x] = how many occurrences of x are currently to the right
    vector<int> cnt(N + 1, 0);

    for (int x : A) cnt[x]++;

    ll ans = 1; // the unchanged sequence

    for (int i = 0; i < N; i++) {
        // Remove A[i], so cnt now represents positions > i.
        cnt[A[i]]--;

        // Only count if i is the start of a run.
        if (i == 0 || A[i] != A[i - 1]) {
            ll right = N - 1 - i;

            // Positions j > i with A[j] != A[i].
            ll different = right - cnt[A[i]];

            ans += different;
        }
    }

    cout << ans << '\n';

    return 0;
}