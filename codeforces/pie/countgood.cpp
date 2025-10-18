#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

long long gcdll(long long a, long long b) {
    return b == 0 ? a : gcdll(b, a % b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    int K;
    cin >> N >> K;
    vector<long long> a(K);
    for (int i = 0; i < K; i++) cin >> a[i];

    long long ans = 0;
    int subsets = 1 << K;
    for (int mask = 0; mask < subsets; mask++) {
        long long lcm = 1;
        int bits = 0;
        bool overflow = false;
        for (int i = 0; i < K; i++) {
            if (mask >> i & 1) {
                bits++;
                long long g = gcdll(lcm, a[i]);
                if (lcm > N / (a[i] / g)) { // prevent overflow
                    overflow = true;
                    break;
                }
                lcm = lcm * (a[i] / g);
            }
        }
        if (overflow || lcm > N) continue;
        long long cnt = N / lcm;
        if (bits % 2 == 0) ans += cnt; // even subset size → add
        else ans -= cnt;               // odd subset size → subtract
    }
    cout << ans << "\n";
}


// wpossiblw subess sof four westaes  wcoutwnerw subsetes wer fo rfour wr wwrstartst wewtsuch ath a teonly common rdiviosr werof theri numbers we is 1 

// hwo do youw erensurewgcd we- 1 we

//  w
// wenubmerhtoewreiwetic werpuctnign werreformaitwl aee wiw tfc wer