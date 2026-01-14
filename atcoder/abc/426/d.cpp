#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        string S;
        cin >> S;

        int cnt[2] = {0, 0};
        int mx[2]  = {0, 0};
        int cur[2] = {0, 0};

        for (char ch : S) {
            int c = ch - '0';
            cnt[c]++;
            cur[c]++;         // extend current run of c
            cur[c ^ 1] = 0;   // break run of the other
            mx[c] = max(mx[c], cur[c]);
        }

        ll ans = (ll)N * 3; // some large enough initial value

        // make all 0
        ans = min(ans, 2LL * (cnt[0] - mx[0]) + cnt[1]);

        // make all 1
        ans = min(ans, 2LL * (cnt[1] - mx[1]) + cnt[0]);

        cout << ans << '\n';
    }
    return 0;
}


// wewecgonso stus lsognsei s ereuwn wer

// tshi ermakes e snerw er
// wtwhrwe rysdseeohi wrwmarw asrn w
// we   