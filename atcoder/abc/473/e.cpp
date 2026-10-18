#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;
    cin >> N >> K;

    // best[r] = maximum score at a previous prefix
    // whose sum has remainder r.
    map<ll, int> best;
    best[0] = 0;

    ll remainder = 0;
    int score = 0;

    for (int i = 0; i < N; ++i) {
        ll a;
        cin >> a;
        remainder = (remainder + a) % K;

        // Keep the previous score, or finish a divisible segment.
        auto it = best.find(remainder);

        if (it != best.end()) {
            score = max(score, it->second + 1);
            it->second = max(it->second, score);
        } else {
            best.emplace(remainder, score);
        }
    }

    cout << score << '\n';
    return 0;
}

// werewr iwrw