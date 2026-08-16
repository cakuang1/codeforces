#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int &x : A) cin >> x;

    // Special case: N = 2
    if (N == 2) {
        // Already non-decreasing
        if (A[0] <= A[1]) {
            cout << "Yes\n";
            cout << 0 << '\n';
            cout << '\n';
            return 0;
        }

        // One operation:
        // (A[0], A[1]) -> (A[1] + K, A[0])
        if (A[1] + K <= A[0]) {
            cout << "Yes\n";
            cout << 1 << '\n';
            cout << 1 << '\n';
            return 0;
        }

        cout << "No\n";
        return 0;
    }

    // For N >= 3, the construction always works.
    const int M = 51;

    vector<int> ans;

    // i here is 1-indexed operation position.
    for (int i = 1; i <= N - 1; ++i) {
        int cnt = 2 * i * M + 1;

        for (int j = 0; j < cnt; ++j) {
            ans.push_back(i);
        }
    }

    cout << "Yes\n";
    cout << ans.size() << '\n';

    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}