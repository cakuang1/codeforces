#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];

        const int MAXA = 10000;
        vector<int> freq(MAXA + 1, 0);
        for (int x : a) freq[x]++;

        vector<int> f(MAXA + 1, 0);
        for (int g = 1; g <= MAXA; g++)
            for (int k = g; k <= MAXA; k += g)
                f[g] += freq[k];

        vector<ll> cnt(MAXA + 1, 0);
        for (int g = MAXA; g >= 1; g--) {
            if (f[g] >= 4)
                cnt[g] = 1LL * f[g] * (f[g] - 1) * (f[g] - 2) * (f[g] - 3) / 24;
            for (int k = 2 * g; k <= MAXA; k += g)
                cnt[g] -= cnt[k];
        }

        cout << cnt[1] << "\n";
    }  
    return 0;}


    // we wer