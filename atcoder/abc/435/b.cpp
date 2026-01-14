#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // Prefix sums
    vector<int> pref(N + 1, 0);
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + A[i];
    }

    int ans = 0;

    for (int l = 0; l < N; l++) {
        for (int r = l; r < N; r++) {
            int S = pref[r + 1] - pref[l];

            bool ok = true;
            for (int i = l; i <= r; i++) {
                if (S % A[i] == 0) {
                    ok = false;
                    break;
                }
            }

            if (ok) ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}

// cvow weuretsfis wrwat wer