#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<pair<int,int>> edges(m + 1);
        for (int i = 1; i <= m; i++) {
            cin >> edges[i].first >> edges[i].second;
        }

        vector<int> used(3 * n + 1, 0);
        vector<int> matching;

        for (int i = 1; i <= m; i++) {
            auto [u, v] = edges[i];
            if (!used[u] && !used[v]) {
                used[u] = used[v] = 1;
                matching.push_back(i);
            }
        }

        if ((int)matching.size() >= n) {
            cout << "Matching\n";
            for (int i = 0; i < n; i++)
                cout << matching[i] << ' ';
            cout << '\n';
        } else {
            cout << "IndSet\n";
            int count = 0;
            for (int i = 1; i <= 3 * n && count < n; i++) {
                if (!used[i]) {
                    cout << i << ' ';
                    count++;
                }
            }
            cout << '\n';
        }
    }
}


