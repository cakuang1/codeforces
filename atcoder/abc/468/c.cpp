#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N), Q(N);
    for (int& x : P) cin >> x;
    for (int& x : Q) cin >> x;

    vector<long long> fac(N + 1, 1);
    for (int i = 1; i <= N; ++i) {
        fac[i] = fac[i - 1] * i;
    }

    auto rankOf = [&](const vector<int>& a) {
        vector<bool> used(N + 1, false);
        long long rank = 0;

        for (int i = 0; i < N; ++i) {
            int smaller = 0;

            for (int x = 1; x < a[i]; ++x) {
                if (!used[x]) ++smaller;
            }

            rank += smaller * fac[N - i - 1];
            used[a[i]] = true;
        }

        return rank;
    };

    cout << max(0LL, rankOf(Q) - rankOf(P) - 1) << '\n';
}