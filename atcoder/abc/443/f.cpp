#include <bits/stdc++.h>
using namespace std;

// ABC443 F - Non-Increasing Number (actually: non-decreasing digits in this editorial approach)
// BFS on states (remainder x, last digit c), packed as idx = 10*x + c.
// Reconstruct the smallest (by length, then lexicographic due to digit order) number divisible by n.
// If impossible, print -1.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int S = 10 * n;
    vector<int> parent(S, -1); // visited marker + backtracking
    queue<int> q;

    // Start state: x=0, c=0 (means "no digit yet", next digit must be >=1)
    parent[0] = 0;   // mark visited; root points to itself
    q.push(0);

    while (!q.empty()) {
        int idx = q.front(); q.pop();
        int c = idx % 10;
        int x = idx / 10;

        for (int cc = max(1, c); cc <= 9; cc++) {
            int xx = ( (x * 10) + cc ) % n;
            int idx2 = xx * 10 + cc;

                if (parent[idx2] != -1) break;

            parent[idx2] = idx;
            q.push(idx2);

            if (xx == 0) {
                // reconstruct answer from idx2 back to 0
                string ans;
                int cur = idx2;
                while (cur != 0) {
                    ans.push_back(char('0' + (cur % 10)));
                    cur = parent[cur];
                }
                reverse(ans.begin(), ans.end());
                cout << ans << "\n";
                return 0;
            }
        }
    }
    cout << -1 << "\n";


    return 0;
}

// w