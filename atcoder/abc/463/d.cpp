#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<pair<long long,long long>> a; // {R, L}
    for (int i = 0; i < N; i++) {
        long long L, R;
        cin >> L >> R;
        a.push_back({R, L});
    }

    sort(a.begin(), a.end());

    auto can = [&](long long d) {
        int cnt = 0;
        long long lastR = -(1LL << 60);

        for (auto [R, L] : a) {
            if (L - lastR >= d) {
                cnt++;
                lastR = R;
                if (cnt >= K) return true;
            }
        }
        return false;
    };

    long long lo = 1, hi = 1e9, ans = -1;

    while (lo <= hi) {
        long long mid = (lo + hi) / 2;

        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << ans << '\n';
}


//w 