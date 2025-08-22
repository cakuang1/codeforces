#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // number of 64‑bit blocks per row
    const int B = (n + 63) / 64;
    // row_bits[i][b] is the b-th 64-bit chunk of row i
    static uint64_t row_bits[3000][(3000 + 63)/64];

    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                int block = j >> 6;        // j / 64
                int offset = j & 63;       // j % 64
                row_bits[i][block] |= (1ull << offset);
            }
        }
    } 

    // w
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        uint64_t* Ri = row_bits[i];
        for (int j = i + 1; j < n; j++) {
            uint64_t* Rj = row_bits[j];
            long long k = 0;
            int b = 0;
            // Unroll by 4
            for (; b + 3 < B; b += 4) {
                k += __builtin_popcountll(Ri[b]   & Rj[b]);
                k += __builtin_popcountll(Ri[b+1] & Rj[b+1]);
                k += __builtin_popcountll(Ri[b+2] & Rj[b+2]);
                k += __builtin_popcountll(Ri[b+3] & Rj[b+3]);
            }
            // Remainder
            for (; b < B; b++) {
                k += __builtin_popcountll(Ri[b] & Rj[b]);
            }
            ans += k * (k - 1) / 2;
        }
    }

    cout << ans << "\n";
    return 0;
}
