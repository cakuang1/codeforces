#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> c(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        sort(c.begin() + 1, c.begin() + n + 1);

        // Two‐pointer scan to find the largest block [i..j] with c[i]+c[i+1]>c[j]
        int j = 3;
        int bestLen = 2;  // worst case: we keep exactly 2 bars (delete n-2)
        for (int i = 1; i <= n - 2; i++) {
            j = max(j, i + 2);
            while (j <= n && c[i] + c[i+1] > c[j]) {
                j++;
            }
            int lastValid = j - 1;
            if (lastValid >= i + 2) {
                int length = (lastValid - i + 1);
                bestLen = max(bestLen, length);
            }
        }

        int answer = n - bestLen;
        cout << answer << "\n";
    }

    return 0;
}
