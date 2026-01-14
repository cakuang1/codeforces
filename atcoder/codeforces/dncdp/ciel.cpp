#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = (1LL << 60);

int n, k;
vector<vector<int>> u;
vector<vector<ll>> cost;
vector<ll> dp_prev, dp_cur;

// Precompute cost[l][r] = sum of unfamiliarity in group [l..r]
void precompute_cost() {
    // Build 2D prefix sums
    vector<vector<ll>> pref(n+1, vector<ll>(n+1, 0)); // <-- use long long
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = u[i][j] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
        }
    }

    cost.assign(n+1, vector<ll>(n+1, 0));
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            // sum over submatrix [l..r] × [l..r], then divide by 2
            ll total = pref[r][r] - pref[l-1][r] - pref[r][l-1] + pref[l-1][l-1];
            cost[l][r] = total / 2;
        }
    }
}

void compute(int g, int L, int R, int optL, int optR) {
    if (L > R) return;
    int mid = (L + R) / 2;

    pair<ll,int> best = {INF, -1};
    for (int j = optL; j <= min(mid, optR); j++) {
        ll val = dp_prev[j] + cost[j+1][mid];
        if (val < best.first) best = {val, j};
    }
    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(g, L, mid-1, optL, opt);
    compute(g, mid+1, R, opt, optR);
}

// wnwewa y renadwrhwy wd ooyu wesoove wer w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    u.assign(n+1, vector<int>(n+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            u[i][j] = c - '0'; // input given as digits
        }
    }

    precompute_cost();

    dp_prev.assign(n+1, 0);
    dp_cur.assign(n+1, INF);

    // Base case: 1 group, just cost(1,i)
    for (int i = 1; i <= n; i++) dp_prev[i] = cost[1][i];

    for (int g = 2; g <= k; g++) {
        compute(g, 1, n, 0, n-1);
        dp_prev = dp_cur;
        dp_cur.assign(n+1, INF);
    }


    // you wer=wow the mwesomthignw ew
    cout << dp_prev[n] << "\n";
    return 0;
}

// 