#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    if (s.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    // run-length encode the string into (digit, length)
    vector<pair<int,int>> counts;
    int runLen = 1;
    char curr = s[0];

    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] != curr) {
            counts.emplace_back(curr - '0', runLen);
            curr = s[i];
            runLen = 1;
        } else {
            runLen++;
        }
    }
    // push the last run
    counts.emplace_back(curr - '0', runLen);

    int ans = 0;
    for (int i = 1; i < (int)counts.size(); i++) {
        // adjacent runs where digit increases by 1
        if (counts[i].first - 1 == counts[i - 1].first) {
            int m = min(counts[i].second, counts[i - 1].second);
            ans += m;
        }
    }

    cout << ans << '\n';
    return 0;
}
