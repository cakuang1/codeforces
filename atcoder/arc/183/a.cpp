#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> cnt(N + 1, K);
    vector<int> ans;

    if (N % 2 == 0) {
        // Median is the last sequence whose first element
        // belongs to the lower half.
        int x = N / 2;

        ans.push_back(x);
        cnt[x]--;

    } else {
        int m = (N + 1) / 2;

        // The median keeps choosing the middle value
        // until all K copies are exhausted.
        for (int i = 0; i < K; i++) {
            ans.push_back(m);
            cnt[m]--;
        }

        // Now N-1 kinds remain, so we are in the even case.
        if (N > 1) {
            ans.push_back(m - 1);
            cnt[m - 1]--;
        }
    }

    // Make the rest lexicographically maximum.
    for (int x = N; x >= 1; x--) {
        while (cnt[x] > 0) {
            ans.push_back(x);
            cnt[x]--;
        }
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}