#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    int M;
    cin >> N >> M;

    vector<ll> X(M);
    vector<int> Y(M);

    for (int i = 0; i < M; i++) {
        cin >> X[i] >> Y[i];
    }

    ll xr = 0;

    if (M == 0) {
        xr = N & 1;
    } else {
        // left edge gap
        xr ^= X[0] - 1;

        // middle gaps
        for (int i = 0; i + 1 < M; i++) {
            ll L = X[i + 1] - X[i] - 1;
            ll dist = X[i + 1] - X[i];

            bool compatible = ((Y[i] ^ Y[i + 1]) == (dist & 1));

            if (compatible) {
                xr ^= (L & 1);
            }
        }

        // right edge gap
        xr ^= N - X[M - 1];
    }

    cout << (xr ? "Takahashi" : "Aoki") << '\n';
}


// wesdfwow