#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int64 sum = 0;
        vector<int64> odd, even;

        for (int i = 0; i < N; i++) {
            int64 x;
            cin >> x;
            sum += x;
            if (x & 1) odd.push_back(x);
            else even.push_back(x);
        }

        sort(odd.rbegin(), odd.rend());
        sort(even.rbegin(), even.rend());

        int O = (int)odd.size();
        int E = (int)even.size();

        int64 best = -1;

        // odd, odd endpoints
        if (O >= 2) {
            int64 changes = 2LL * min(E, O - 1);
            best = max(best, odd[0] + odd[1] + changes);
        }

        // even, even endpoints
        if (E >= 2) {
            int64 changes = 2LL * min(O, E - 1);
            best = max(best, even[0] + even[1] + changes);
        }

        // one odd endpoint, one even endpoint
        if (O >= 1 && E >= 1) {
            int64 changes = 2LL * min(O, E) - 1;
            best = max(best, odd[0] + even[0] + changes);
        }

        cout << sum - best / 2 << '\n';
    }
}