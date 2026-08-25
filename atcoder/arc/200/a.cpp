#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<ll> A(N), B(N);
        for (ll &x : A) cin >> x;
        for (ll &x : B) cin >> x;

        int j = -1;

        // Compare A[i] / B[i] with A[0] / B[0]
        for (int i = 1; i < N; i++) {
            if (A[i] * B[0] != A[0] * B[i]) {
                j = i;
                break;
            }
        }

        if (j == -1) {
            // A is a positive scalar multiple of B,
            // so A·X and B·X can never have opposite signs.
            cout << "No\n";
            continue;
        }

        vector<ll> X(N, 0);

        int i = 0;

        /*
            We want to choose signs depending on

                D = A[j] * B[i] - A[i] * B[j].

            If D > 0, use:
                X[i] = -(A[j] + B[j])
                X[j] =  (A[i] + B[i])

            Then:
                A·X = D > 0
                B·X = -D < 0

            If D < 0, negate both X values.
        */

        ll D = A[j] * B[i] - A[i] * B[j];

        X[i] = -(A[j] + B[j]);
        X[j] =  (A[i] + B[i]);

        if (D < 0) {
            X[i] = -X[i];
            X[j] = -X[j];
        }

        cout << "Yes\n";
        for (int k = 0; k < N; k++) {
            if (k) cout << ' ';
            cout << X[k];
        }
        cout << '\n';
    }

    return 0;
}