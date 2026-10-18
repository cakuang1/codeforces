#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Fenwick {
    int n;
    vector<int> tree;

    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    void add(int index, int value) {
        for (; index <= n; index += index & -index) {
            tree[index] += value;
        }
    }

    int sum(int index) const {
        int result = 0;
        for (; index > 0; index -= index & -index) {
            result += tree[index];
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<ll, int>> s(n), t(n);

    for (int i = 0; i < n; ++i) {
        cin >> s[i].first;
        s[i].second = i;
    }

    for (int i = 0; i < n; ++i) {
        cin >> t[i].first;
        t[i].second = i;
    }

    // Assuming net means the original sum of |A[i] - B[i]|.
    ll net = 0;
    for (int i = 0; i < n; ++i) {
        net += abs(s[i].first - t[i].first);
    }

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    // Rank in sorted t for each original index.
    vector<int> tind(n);
    for (int i = 0; i < n; ++i) {
        tind[t[i].second] = i;
    }

    vector<int> match(n);
    for (int i = 0; i < n; ++i) {
        match[i] = tind[s[i].second];
    }

    Fenwick bit(n);
    ll inter = 0;

    for (int i = 0; i < n; ++i) {
        int rank = match[i] + 1; // Fenwick uses 1-based indices.

        // Count earlier endpoints with a greater rank.
        inter += (ll)i - bit.sum(rank);
        bit.add(rank, 1);
    }

    cout << net - inter << '\n';

    return 0;
}