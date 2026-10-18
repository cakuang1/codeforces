#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;

using ull = unsigned long long;
using mint = atcoder::modint998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, M;
    ull seed;
    cin >> N >> K >> seed >> M;

    vector<int> b(M), V(K);
    for (int& x : b) cin >> x;
    for (int& x : V) cin >> x;

    // cnt[d][a]: occurrences of adjacent pair (a, (a+d) % K).
    vector<vector<int>> cnt(K, vector<int>(K));

    ull state = seed;
    int first = -1, previous = -1;

    for (int i = 0; i < N; ++i) {
        int current;

        if (i < M) {
            current = b[i];
        } else {
            ull x = (((state >> 18) ^ state) >> 27)
                  & 0xFFFFFFFFULL;
            ull r = state >> 59;
            ull y = ((x >> r) + (x << (32 - r)))
                  & 0xFFFFFFFFULL;

            current = y % K;

            // Update only when generating an element.
            state = state * 6364136223846793005ULL
                          + 2026081520260815ULL;
        }

        if (i == 0) {
            first = current;
        } else {
            int d = current - previous;
            if (d < 0) d += K;
            ++cnt[d][previous];
        }

        previous = current;
    }

    vector<mint> ans(K);

    // First position starts a syllable if it is a vowel.
    for (int k = 0; k < K; ++k) {
        ans[k] = V[(first + k) % K];
    }

    // Handle each difference separately.
    for (int d = 0; d < K; ++d) {
        vector<mint> reversed(K), pattern(K);
        bool hasPairs = false, hasStarts = false;

        for (int a = 0; a < K; ++a) {
            // Circular reversal of the counts.
            reversed[(K - a) % K] = cnt[d][a];
            hasPairs |= (cnt[d][a] != 0);

            int next = (a + d) % K;

            // Non-vowel -> vowel starts a syllable.
            int start#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MOD2 = 998244353;
const ll INF = 1'000'000'000'000'000'000LL;
const int MX = 1000001; // Valid factorial indices: 0 ... MX-1

ll modExp(ll base, ll power) {
    base %= MOD;
    if (base < 0) base += MOD;

    ll result = 1;
    while (power > 0) {
        if (power & 1) result = result * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return result;
}


// webiwet. s ssorw rw




ll inv(ll base) {
    // Requires base != 0 (mod MOD), and MOD prime.
    return modExp(base, MOD - 2);
}

// These helpers assume 0 <= A, B < MOD.
ll mul(ll A, ll B) {
    return A * B % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll facs[MX], facInvs[MX];

void initFacs() {
    facs[0] = 1;
    for (int i = 1; i < MX; ++i) {
        facs[i] = mul(facs[i - 1], i);
    }

    facInvs[MX - 1] = inv(facs[MX - 1]);
    for (int i = MX - 1; i >= 1; --i) {
        facInvs[i - 1] = mul(facInvs[i], i);
    }
}

ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment if you need choose():
    // initFacs();

    return 0;
}s = (1 - V[a]) * V[next];
            pattern[a] = starts;
            hasStarts |= (starts != 0);
        }

        if (!hasPairs || !hasStarts) continue;

        auto product = atcoder::convolution(reversed, pattern);

        // Wrap convolution indices around the circle.
        for (int i = 0; i < (int)product.size(); ++i) {
            ans[i % K] += product[i];
        }
    }

    for (mint answer : ans) {
        cout << answer.val() << '\n';
    }

    return 0;
}