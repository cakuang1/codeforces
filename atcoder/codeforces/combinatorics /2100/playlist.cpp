#include <bits/stdc++.h>
#include <cstring>  // for memset
using namespace std;

using ll = long long;
const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MX = 1000001; // not used here

ll modExp(ll base, ll power) {
    if (power == 0) {
        return 1;
    } else {
        ll cur = modExp(base, power / 2);
        cur = (cur * cur) % MOD;
        if (power % 2 == 1)
            cur = (cur * base) % MOD;
        return cur % MOD;
    }
}

ll inv(ll base) {
    return modExp(base, MOD-2);
}

ll mul(ll A, ll B) {
    return (A * B) % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll* facs = new ll[MX];
ll* facInvs = new ll[MX];

ll choose(ll a, ll b) {
    if (b > a) return 0;
    if (a < 0) return 0;
    if (b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a-b]);
    return cur;
}

void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MOD; i++) {
        facs[i] = (facs[i-1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

// Constants for DP dimensions.
const int MAXN = 15;
const int MAXT = 226;
const int MAXG = 4;  // We'll use genre indices 1..3; 0 is reserved as the initial (empty) state.

// dp[mask][duration][last_genre]
ll dp[1 << MAXN][MAXT][MAXG];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, T; 
    cin >> n >> T;
    vector<pair<int,int>> songs(n);
    
    // Initialize dp array to 0.
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        cin >> songs[i].first >> songs[i].second;
    }
    
    
    // Initialize starting states: choose each song as the first song.
    for (int i = 0; i < n; i++) {
        int dur = songs[i].first;
        int gen = songs[i].second;  // genre in {1, 2, 3}
        if (dur <= T)
            dp[1 << i][dur][gen] = add(dp[1 << i][dur][gen], 1);
    }
    
    // DP over all subsets of songs.
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int duration = 0; duration <= T; duration++) {
            for (int lastGen = 0; lastGen < MAXG; lastGen++) {
                if (dp[mask][duration][lastGen] == 0) continue;
                // Try to add a new song (that is not used yet).
                for (int next = 0; next < n; next++) {
                    if (mask & (1 << next)) continue; // Song 'next' already used.
                    int nextGen = songs[next].second;
                    // If we already have a song (lastGen != 0), require that the next song's genre is different.
                    if (lastGen != 0 && nextGen == lastGen) continue;
                    int nextDur = songs[next].first;
                    if (duration + nextDur <= T) {
                        dp[mask | (1 << next)][duration + nextDur][nextGen] =
                            add(dp[mask | (1 << next)][duration + nextDur][nextGen], dp[mask][duration][lastGen]);
                    }
                }
            }
        }
    }
    
    // Final answer: sum over all masks (not just the full mask) and over all last_genre in {1,2,3}
    // such that total duration equals T.
    ll res = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int gen = 1; gen < MAXG; gen++) {
            res = add(res, dp[mask][T][gen]);
        }
    }
    
    cout << res % MOD << "\n";
    return 0;
}
