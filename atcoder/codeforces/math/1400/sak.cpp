#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> p(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
        }

        vector<bool> visited(n+1, false);
        ll ans = 0;

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                // Follow this cycle
                int curr = i;
                int length = 0;
                while (!visited[curr]) {
                    visited[curr] = true;
                    curr = p[curr];
                    length++;
                }
                // If its length >= 3, it costs floor(length/2) swaps
                if (length >= 3) {
                    ans += ((length - 1)/ 2);
                }
                // length=1 or 2 cost zero swaps
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
