#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> A(N);
    for (auto &x : A) cin >> x;

    // pref[i]: first i elements are sorted.
    // suff[i]: elements i through N-1 are sorted.
    vector<bool> pref(N + 1, true), suff(N + 1, true);

    for (int i = 2; i <= N; ++i) {
        pref[i] = pref[i - 1] && A[i - 2] <= A[i - 1];
    }

    for (int i = N - 2; i >= 0; --i) {
        suff[i] = suff[i + 1] && A[i] <= A[i + 1];
    }

    deque<int> minQ, maxQ;

    for (int r = 0; r < N; ++r) {
        int l = r - K + 1;

        // Remove indices outside the current window.
        while (!minQ.empty() && minQ.front() < l)
            minQ.pop_front();
        while (!maxQ.empty() && maxQ.front() < l)
            maxQ.pop_front();

        // Maintain increasing values in minQ.
        while (!minQ.empty() && A[minQ.back()] >= A[r])
            minQ.pop_back();
        minQ.push_back(r);

        // Maintain decreasing values in maxQ.
        while (!maxQ.empty() && A[maxQ.back()] <= A[r])
            maxQ.pop_back();
        maxQ.push_back(r);

        if (l < 0) continue;

        long long mn = A[minQ.front()];
        long long mx = A[maxQ.front()];

        bool valid = pref[l] && suff[r + 1];

        if (l > 0 && A[l - 1] > mn)
            valid = false;

        if (r + 1 < N && mx > A[r + 1])
            valid = false;

        if (valid) {
            cout << "Yes\n";
            return 0;
        }
    }

    cout << "No\n";
    return 0;
}