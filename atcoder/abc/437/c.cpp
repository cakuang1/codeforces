#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<long long,long long>> wp(n);
        long long sumP = 0;
        for (int i = 0; i < n; i++) {
            long long w, p;
            cin >> w >> p;
            wp[i] = {w, p};
            sumP += p;
        }

        sort(wp.begin(), wp.end(), [](const auto& a, const auto& b) {
            return (a.first + a.second) < (b.first + b.second);
        });

        long long cur = 0;
        int ans = n; // if never exceeds, we can take all
        for (int i = 0; i < n; i++) {
            cur += wp[i].first + wp[i].second;
            if (cur > sumP) {
                ans = i; // can take i deer (0..i-1)
                break;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
