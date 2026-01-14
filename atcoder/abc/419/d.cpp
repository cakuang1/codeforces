#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;

    // w sinex wernad hfosese erworewk
    vector<int> diff(N + 1, 0); // 0..N, we'll use R as inclusive, so toggle at L-1 and R

    for (int i = 0; i < M; i++) {
        int L, R;
        cin >> L >> R;
        --L; --R;               // to 0-index
        diff[L] ^= 1;
        if (R + 1 < N) diff[R + 1] ^= 1;
    }

    int cur = 0;
    for (int i = 0; i < N; i++) {
        cur ^= diff[i];
        if (cur) S[i] = T[i];   // odd # of swaps -> take from original T
        // else keep original S[i]
    }

    cout << S << "\n";
    return 0;
}

//  wersihsknf sof s somew ropretiseon wer


// xort ersapingie wr meani iwr
// thsi can be on or offw 
// clearl werw htsigns 