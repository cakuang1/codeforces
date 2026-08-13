#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> P(Q);
    vector<long long> V(Q);

    for (int i = 0; i < Q; i++) {
        cin >> P[i] >> V[i];
    }

    // dir[i]:
    // 0 = not forced
    // 1 = left  (paint [1..P[i]])
    // 2 = right (paint [P[i]..N])
    vector<int> dir(Q, 0);

    auto force_dir = [&](int i, int d) -> bool {
        if (dir[i] == 0) {
            dir[i] = d;
            return true;
        }

        // Already forced the opposite way.
        return dir[i] == d;
    };

    for (int i = 0; i < Q; i++) {
        for (int j = i + 1; j < Q; j++) {

            // Earlier value isn't larger, so j can safely overwrite it.
            if (V[i] <= V[j]) continue;

            // Now V[i] > V[j].
            // The two painted ranges must not intersect.

            if (P[i] == P[j]) {
                cout << 0 << '\n';
                return 0;
            }

            if (P[i] < P[j]) {
                // i must paint left, j must paint right.
                if (!force_dir(i, 1) || !force_dir(j, 2)) {
                    cout << 0 << '\n';
                    return 0;
                }
            } else {
                // P[i] > P[j]
                // i must paint right, j must paint left.
                if (!force_dir(i, 2) || !force_dir(j, 1)) {
                    cout << 0 << '\n';
                    return 0;
                }
            }
        }
    }

    // Every unforced operation has two independent choices.
    long long ans = 1;

    for (int i = 0; i < Q; i++) {
        if (dir[i] == 0) {
            ans = ans * 2 % MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}

// w