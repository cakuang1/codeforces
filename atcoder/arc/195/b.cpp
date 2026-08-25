#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N), B(N);
    for (ll &x : A) cin >> x;
    for (ll &x : B) cin >> x;

    map<ll, int> cntA, cntB;

    int wildA = 0, wildB = 0;
    ll mx = 0;

    for (ll x : A) {
        if (x == -1) {
            wildA++;
        } else {
            cntA[x]++;
            mx = max(mx, x);
        }
    }

    for (ll x : B) {
        if (x == -1) {
            wildB++;
        } else {
            cntB[x]++;
            mx = max(mx, x);
        }
    }

    // Number of positions that MUST be fixed-fixed matches.
    int need = N - wildA - wildB;

    // If we have enough -1s that every position can contain
    // at least one flexible value, we can always make it work.
    if (need <= 0) {
        cout << "Yes\n";
        return 0;
    }

    // For every possible pair of fixed values:
    //
    // x from A and y from B contribute
    // min(cntA[x], cntB[y]) to f(x + y).
    //
    // There are at most N^2 such pairs.
    vector<pair<ll, int>> contributions;
    contributions.reserve((size_t)cntA.size() * cntB.size());

    for (auto [x, cx] : cntA) {
        for (auto [y, cy] : cntB) {
            contributions.push_back({
                x + y,
                min(cx, cy)
            });
        }
    }

    sort(contributions.begin(), contributions.end());

    // Add together all contributions belonging to the same z.
    for (int i = 0; i < (int)contributions.size(); ) {
        int j = i;
        ll z = contributions[i].first;
        int f = 0;

        while (j < (int)contributions.size() &&
               contributions[j].first == z) {
            f += contributions[j].second;
            j++;
        }

        // z must be at least every fixed value,
        // otherwise some required replacement would be negative.
        if (z >= mx && f >= need) {
            cout << "Yes\n";
            return 0;
        }

        i = j;
    }

    cout << "No\n";
    return 0;
}