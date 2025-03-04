#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD2 = 998244353; 
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001;

ll modExp(ll base, ll power) {
    if (power == 0) {
        return 1;
    } else {
        ll cur = modExp(base, power / 2); 
        cur = cur * cur % MOD;
        if (power % 2 == 1) cur = cur * base % MOD;
        return cur;
    }
}

ll inv(ll base) {
	return modExp(base, MOD - 2);
}

ll mul(ll A, ll B) {
	return (A * B) % MOD;
}

ll add(ll A, ll B) {
	return (A + B) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
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
    cur = mul(cur, facInvs[a - b]);
    return cur;
}

void initFacs() {
	facs[0] = 1;
	facInvs[0] = 1;
	for (int i = 1; i < MOD; i++) {
		facs[i] = (facs[i - 1] * i) % MOD;
		facInvs[i] = inv(facs[i]);
	}
}

// Corrected solve: For a given favorite number group, we have:
//  - 'players' = number of players having that favorite number.
//  - 'cards'   = number of cards available with that number.
//  - 'h'       = vector of joy levels h[0..k-1], where h[t-1] = joy if a player gets t cards (t>=1)
// Each player can get at most k cards.
// We want to distribute at most min(cards, players * k) cards among the players.
ll solve(int players, int cards, const vector<ll> &h) {
    int k = h.size(); 
    int maxCards = min(cards, players * k);
    
    // dp[i][j] = maximum total joy distributing j cards among first i players.
    // Initialize with -infinity for impossible states.
    vector<vector<ll>> dp(players + 1, vector<ll>(maxCards + 1, -1));
    dp[0][0] = 0;
    
    for (int i = 1; i <= players; i++) {
        for (int j = 0; j <= maxCards; j++) {
            // Try giving t cards to the i-th player (t from 0 to k, but cannot exceed j)
            for (int t = 0; t <= k && t <= j; t++) {
                if (dp[i - 1][j - t] == -1) continue;
                ll addJoy = (t == 0 ? 0 : h[t - 1]);
                dp[i][j] = max(dp[i][j], dp[i - 1][j - t] + addJoy);
            }
        }
    }
    return dp[players][maxCards];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);   

    int n, k;
    cin >> n >> k;
    
    // Read all k*n cards.
    unordered_map<int,int> counts; 
    for (int i = 0; i < n * k; i++) {
        int card; 
        cin >> card;
        counts[card]++;
    }
    
    // Read favorite numbers of the n players.
    unordered_map<int,int> fav;
    for (int i = 0; i < n; i++) {
        int curr; 
        cin >> curr;
        fav[curr]++;
    }
    
    // Read joy levels h1,...,hk.
    // Note: For a player, if he gets t cards (1 <= t <= k) his joy is h_t.
    vector<ll> h(k);
    for (int i = 0; i < k; i++) {
        cin >> h[i];
    }
    
    ll res = 0; 
    // For each distinct favorite number, solve the subproblem.
    // Only players whose favorite number appears on some cards can get nonzero joy.
    for (auto &p : fav) {
        int card = p.first; 
        int playerCount = p.second;
        int available = counts[card];
        res += solve(playerCount, available, h);    
    }
         
    cout << res << "\n"; 
    return 0;
}
