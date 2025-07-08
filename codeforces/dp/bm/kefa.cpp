#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll NEG = LLONG_MIN / 4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // bonus[x][y] = extra satisfaction if you eat x immediately before y
    vector<vector<ll>> bonus(n, vector<ll>(n, 0));
    for(int i = 0; i < k; i++){
        int x, y; ll c;
        cin >> x >> y >> c;
        --x; --y;
        bonus[x][y] = c;
    }

    // dp[mask][last] = max satisfaction for picking exactly popcount(mask) dishes,
    // ending with dish 'last' (and mask includes 'last')
    int FULL = (1<<n) - 1;
    vector<vector<ll>> dp(1<<n, vector<ll>(n, NEG));

    // seed: single-dish sequences
    for(int i = 0; i < n; i++){
        dp[1<<i][i] = a[i];
    }

    ll answer = 0;
    // iterate over all subsets
    for(int mask = 0; mask <= FULL; mask++){
        int cnt = __builtin_popcount(mask);
        // for every possible last dish in 'mask'
        for(int last = 0; last < n; last++){
            if(!(mask & (1<<last))) continue;   // last must be in mask
            ll cur = dp[mask][last];
            if(cur == NEG) continue;            // unreachable state

            // if we've already chosen m dishes, update final answer
            if(cnt == m){
                answer = max(answer, cur);
                continue;
            }
            // otherwise, try to pick a new dish j not in mask
            for(int j = 0; j < n; j++){
                if(mask & (1<<j)) continue;
                int nm = mask | (1<<j);
                ll gain = a[j] + bonus[last][j];
                dp[nm][j] = max(dp[nm][j], cur + gain);
            }
        }
    }

    cout << answer << "\n";
    return 0;
}
