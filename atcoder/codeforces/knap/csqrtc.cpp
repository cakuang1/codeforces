#include <bits/stdc++.h>
using namespace std;

// Compress multiplicities with pair-and-carry
vector<int> compress(const vector<int>& weights) {
    map<int,int> count;
    for (int w : weights) count[w]++;

    vector<int> eff;
    while (!count.empty()) {
        auto [w, occ] = *count.begin();
        count.erase(count.begin());

        if (occ % 2 == 1) eff.push_back(w);
        if (occ >= 2) eff.push_back(w);

        int pairs = occ / 2;
        if (pairs > 0) count[w*2] += pairs;
    }
    return eff;
}

// Subset sum with bitset DP
vector<bool> subsetSum(const vector<int>& weights, int C) {
    auto eff = compress(weights);

    vector<unsigned long long> dp((C>>6)+1, 0ULL); // bitset in 64-bit chunks
    dp[0] = 1ULL; // dp[0] = true

    for (int w : eff) {
        int shift = w >> 6;       // how many 64-bit blocks to shift
        int offset = w & 63;      // bit offset inside block

        auto ndp = dp; // copy

        for (int i = 0; i < (int)dp.size(); i++) {
            unsigned long long val = dp[i];
            if (!val) continue;

            // case 1: shift inside same block
            if (i+shift < (int)dp.size())
                ndp[i+shift] |= (val << offset);

            // case 2: bits spill into next block
            if (offset && i+shift+1 < (int)dp.size())
                ndp[i+shift+1] |= (val >> (64-offset));
        }

        dp.swap(ndp);
    }

    vector<bool> result(C+1, false);
    for (int i = 0; i < (int)dp.size(); i++) {
        unsigned long long val = dp[i];
        for (int b = 0; b < 64 && (i<<6)+b <= C; b++) {
            if (val & (1ULL << b))
                result[(i<<6)+b] = true;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<int> w(N);
    int C = 0;
    for (int i = 0; i < N; i++) {
        cin >> w[i];
        C += w[i];
    }

    auto res = subsetSum(w, C);

    for (int k = 1; k <= C; k++) {
        if (res[k]) cout << k << " ";
    }
    cout << "\n";
}
