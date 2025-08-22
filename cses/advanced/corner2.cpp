#pragma GCC target("avx2,bmi2,popcnt")
#pragma GCC optimize("Ofast,unroll-loops,inline")
#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 3000;
static uint64_t bits[26][MAXN][(MAXN+63)/64];
static int cnts[26][MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    const int B = (n + 63) >> 6;

    // 1) Read input, build bit‐masks and counts
    string row;
    for(int i = 0; i < n; i++){
        cin >> row;
        for(int j = 0; j < n; j++){
            int L = row[j] - 'A';
            if ((unsigned)L < (unsigned)k) {
                int w = j >> 6, off = j & 63;
                bits[L][i][w] |= (1ull << off);
                cnts[L][i]++;
            }
        }
    }

    // 2) Process each letter
    for(int L = 0; L < k; L++){
        // collect rows with >=2 of this letter
        vector<int> R;
        R.reserve(64);
        for(int i = 0; i < n; i++){
            if (cnts[L][i] >= 2)
                R.push_back(i);
        }
        if (R.size() < 2) {
            cout << "NO\n";
            continue;
        }

        // try every pair, stop as soon as we find 2 shared bits
        bool ok = false;
        int G = R.size();
        for(int a = 0; a + 1 < G && !ok; ++a){
            uint64_t* Abits = bits[L][ R[a] ];
            for(int b = a + 1; b < G; ++b){
                uint64_t* Bbits = bits[L][ R[b] ];
                int shared = 0;
                // hand‑unrolled by 4 blocks per iteration
                int w = 0;
                for(; w + 3 < B && shared < 2; w += 4){
                    uint64_t x0 = Abits[w  ] & Bbits[w  ];
                    uint64_t x1 = Abits[w+1] & Bbits[w+1];
                    uint64_t x2 = Abits[w+2] & Bbits[w+2];
                    uint64_t x3 = Abits[w+3] & Bbits[w+3];
                    shared += __builtin_popcountll(x0)
                            + __builtin_popcountll(x1)
                            + __builtin_popcountll(x2)
                            + __builtin_popcountll(x3);
                }
                for(; w < B && shared < 2; ++w){
                    shared += __builtin_popcountll(Abits[w] & Bbits[w]);
                }
                if (shared >= 2){
                    ok = true;
                    break;
                }
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
