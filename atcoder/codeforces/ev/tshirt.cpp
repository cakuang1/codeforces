#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 3000;
static const int MAXM = 300;
static const double EPS_EXTEND = 1e-12;  // threshold to extend support
static const double TINY = 1e-50;        // zeroing threshold
static const double NEG_INF = -1e100;

int n, m;

// p[size][engineer] = probability engineer fits size
double p[MAXM + 1][MAXN + 1];

// q[size][i] = Pr[D_size = i], len[size] = highest i with non-negligible mass
double q[MAXM + 1][MAXN + 1];
int lenv[MAXM + 1];

// e[size][y] = E[min(D_size, y)]
double eexp[MAXM + 1][MAXN + 1];

// DP over sizes and used shirts
double dp[MAXM + 1][MAXN + 1];

// In-place PMF update for one Bernoulli(prob)
inline void update_pmf(int t, double prob) {
    int L = lenv[t];
    for (int i = L; i >= 0; --i) {
        q[t][i + 1] += q[t][i] * prob;
        q[t][i] *= (1.0 - prob);
        if (q[t][i] < TINY) q[t][i] = 0.0;
    }
    // Extend support only if the new tail is non-negligible
    if (q[t][L + 1] >= EPS_EXTEND) {
        lenv[t] = L + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // Read probabilities: input is per engineer i, size j
    // We'll store p[j][i] = prob(i fits size j)
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int tmp; cin >> tmp;
            p[j][i] = tmp / 1000.0;
        }
    }

    // Build PMFs q for each size
    for (int t = 1; t <= m; ++t) {
        memset(q[t], 0, sizeof(q[t]));
        q[t][0] = 1.0;
        lenv[t] = 0;
        for (int i = 1; i <= n; ++i) {
            if (p[t][i] <= 0.0) continue;
            if (p[t][i] >= 1.0) {
                // deterministic increment by 1
                for (int k = lenv[t]; k >= 0; --k) q[t][k + 1] += q[t][k], q[t][k] = 0.0;
                ++lenv[t];
                continue;
            }
            update_pmf(t, p[t][i]);
        }
        // Optional: clean tiny noise
        for (int i = 0; i <= lenv[t]; ++i) if (q[t][i] < TINY) q[t][i] = 0.0;
        // Normalize (just in case of tiny drift)
        double sum = 0.0; for (int i = 0; i <= lenv[t]; ++i) sum += q[t][i];
        if (sum > 0) { for (int i = 0; i <= lenv[t]; ++i) q[t][i] /= sum; }
    }

    // Precompute eexp[t][y] = E[min(D_t, y)].
    // Use prefix sums for O(n) per size.
    for (int t = 1; t <= m; ++t) {
        // Compute E[D_t] and prefix sums of q
        double ED = 0.0;
        for (int i = 0; i <= lenv[t]; ++i) ED += i * q[t][i];

        // Build eexp[t][y] for y = 0..n
        double prefP = 0.0; // sum_{i=0}^{y-1} q[i]
        double prefS = 0.0; // sum_{i=0}^{y-1} i*q[i]

        eexp[t][0] = 0.0; // min(D,0)=0
        for (int y = 1; y <= n; ++y) {
            int idx = y - 1;
            // extend prefixes by q[idx] if within support
            if (idx <= lenv[t]) {
                prefP += q[t][idx];
                prefS += idx * q[t][idx];
            }
            // E[min(D,y)] = sum_{i=0}^{y-1} i*q[i] + y * (1 - sum_{i=0}^{y-1} q[i])
            // but once y > lenv[t], prefP becomes 1.0 (numerically), value flattens to ED
            double val = prefS + y * max(0.0, 1.0 - prefP);
            // guard against tiny numeric bumps beyond support
            if (y > lenv[t] && fabs(val - ED) < 1e-13) val = ED;
            eexp[t][y] = val;
        }
        // If numeric drift, enforce tail to ED
        for (int y = lenv[t] + 1; y <= n; ++y) eexp[t][y] = ED;
    }

    // Knapsack over sizes: dp[i][j] = max expected covered using first i sizes and j shirts
    for (int i = 0; i <= m; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = NEG_INF;
    dp[0][0] = 0.0;

    for (int i = 1; i <= m; ++i) {
        // For each total shirts j, choose y shirts for size i
        for (int j = 0; j <= n; ++j) {
            // Only need y up to min(j, lenv[i]); giving more than lenv[i] never improves value
            int ymax = min(j, lenv[i]);
            double best = NEG_INF;
            for (int y = 0; y <= ymax; ++y) {
                if (dp[i - 1][j - y] == NEG_INF) continue;
                best = max(best, dp[i - 1][j - y] + eexp[i][y]);
            }
            dp[i][j] = best;
        }

        // 
    }


    // w dfwrdo shti rmakes sen erw
    cout.setf(std::ios::fixed); cout << setprecision(12) << dp[m][n] << "\n";
    return 0;
}


// wrin werdfs in w
// wnow rsconseriting wr