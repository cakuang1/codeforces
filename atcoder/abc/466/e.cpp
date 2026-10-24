#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    K = min(K, N);

    vector<ll> A(N), B(N);

    ll baseline = 0;
    for (ll& a : A) {
        cin >> a;
        baseline += a;
    }
    for (ll& b : B) cin >> b;

    
    vector<ll> off(K + 1, NEG), on(K + 1, NEG);
    off[0] = 0;

    for (int i = 0; i < N; ++i) {
        ll gain = B[i] - A[i];

        vector<ll> nextOff(K + 1, NEG);
        vector<ll> nextOn(K + 1, NEG);

        for (int j = 0; j <= K; ++j) {
            // Leave this card front-side up.
            nextOff[j] = max(off[j], on[j]);

            // Continue an existing back-facing interval.
            if (on[j] != NEG) {
                nextOn[j] = on[j] + gain;
            }

            // Start a new back-facing interval.
            if (j > 0 && off[j - 1] != NEG) {
                nextOn[j] = max(nextOn[j], off[j - 1] + gain);
            }
        }

        off.swap(nextOff);
        on.swap(nextOn);
    }

    ll bestGain = 0;
    for (int j = 0; j <= K; ++j) {
        bestGain = max({bestGain, off[j], on[j]});
    }

    cout << baseline + bestGain << '\n';
}

