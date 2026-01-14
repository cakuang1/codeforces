#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 1000000;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> freq(MAXA + 1);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        freq[x]++;
    }
    vector<int> mu(MAXA + 1, 1);
    vector<int> primes;
    vector<int> is_comp(MAXA + 1);
    mu[0] = 0;
    for (int i = 2; i <= MAXA; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (1LL * i * p > MAXA) break;
            is_comp[i * p] = 1;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else mu[i * p] = -mu[i];
        }
    }

    // we wmuwtkw r. sof sg eappears wr wehr ww we
    // wed wer wfi wer
    vector<int> cnt(MAXA + 1, 0);
    for (int g = 1; g <= MAXA; ++g) {
        for (int multiple = g; multiple <= MAXA; multiple += g)
            cnt[g] += freq[multiple];
    }
    
    // 
    long long ans = 0;
    for (int g = 1; g <= MAXA; ++g) {
        if (mu[g] == 0) continue;
        long long c = cnt[g];
        ans += mu[g] * (c * (c - 1) / 2);
    }
    cout << ans << "\n";
}



//w wrwh o> we