#include <bits/stdc++.h>
using namespace std;

int LIS(const vector<int>& arr) {
    vector<int> tail;
    for (int x : arr) {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return tail.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> A(n), B(n), pos(n+1);
        for (int i = 0; i < n; i++) cin >> A[i];
        for (int i = 0; i < n; i++) {
            cin >> B[i];
            pos[B[i]] = i;
        }

        // Map A into positions in B
        vector<int> mapped(n);
        for (int i = 0; i < n; i++) {
            mapped[i] = pos[A[i]];
        }

        int L = LIS(mapped);
        cout << 2 * (n - L) << "\n";
    }
}


