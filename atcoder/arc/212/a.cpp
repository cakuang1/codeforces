#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    int64 ans = 0;

    // A = x12 + x34
    // B = x13 + x24
    // C = x14 + x23
    //
    // Since every original edge weight is positive,
    // A, B, C are all at least 2.
    for (int A = 2; A <= K; ++A) {
        for (int B = 2; B <= K; ++B) {
            int C = K - A - B;

            if (C < 2) continue;

            // Number of ways to split:
            //
            // x12 + x34 = A : A-1 ways
            // x13 + x24 = B : B-1 ways
            // x14 + x23 = C : C-1 ways
            int64 ways = 1LL * (A - 1) * (B - 1) % MOD;
            ways = ways * (C - 1) % MOD;

            // The three Hamiltonian cycles have costs:
            //
            // K-A, K-B, K-C
            //
            // so the minimum is:
            int f = K - max({A, B, C});

            ans = (ans + ways * f) % MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}

// weewsd ws owhw
// cearl werwouwe// wrn sers ssn weur

// [] 
// []
// wtw eraro wer

/// how sdo otwuo corecthsi wer


// [x,y]

// need correction 


// [y,x]



// wnew wers hsi oc sower

// werwho sofuosd sseirw


// how wotuwo sorecsts issf elf wer



    // wewrsdhrelalr wrpw rw
    / w
    // 
// or some path way to fix this

