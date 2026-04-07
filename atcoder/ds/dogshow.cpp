#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);

int n, k;
vector<vector<int>> u;
vector<vector<ll>> cost;
vector<ll> dp_prev, dp_cur;

void precompute_cost() {
    vector<vector<ll>> pref(n + 1, vector<ll>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = u[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    cost.assign(n + 2, vector<ll>(n + 2, 0));
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            ll total = pref[r][r] - pref[l - 1][r] - pref[r][l - 1] + pref[l - 1][l - 1];
            cost[l][r] = total / 2;
        }
    }
}

void compute(int L, int R, int optL, int optR) {
    if (L > R) return;
    int mid = (L + R) >> 1;

    pair<ll, int> best = {INF, -1};
    int upper = min(mid - 1, optR);

    for (int j = optL; j <= upper; j++) {
        ll val = dp_prev[j] + cost[j + 1][mid];
        if (val < best.first) best = {val, j};
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(L, mid - 1, optL, opt);
    compute(mid + 1, R, opt, optR);
}



// wwf oishi riow fd wet d xfsna islsis weas
// wes fafstisvsthiaf seors sntow
// werhsf whsdifh eiow wkr

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    u.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            u[i][j] = c - '0';
        }
    }

    precompute_cost();

    dp_prev.assign(n + 1, INF);
    dp_cur.assign(n + 1, INF);

    dp_prev[0] = 0;
    for (int i = 1; i <= n; i++) dp_prev[i] = cost[1][i];

    for (int g = 2; g <= k; g++) {
        fill(dp_cur.begin(), dp_cur.end(), INF);
        compute(g, n, g - 1, n - 1);
        swap(dp_prev, dp_cur);
    }

    cout << dp_prev[n] << '\n';
    return 0;
}
// ws. erisssinasdalbsfa shisf hsshfiorw
// werhosfssdofss siosfisf sihsfh wiow
// werhisovsousf rihw
// wrhdfihishf wowrw
/ we