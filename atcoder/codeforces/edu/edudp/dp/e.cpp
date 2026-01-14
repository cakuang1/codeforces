#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;  // Large value for unreachable states

// Function to compute cost of picking a key and reaching the office
ll findCost(ll person, ll key, ll office) {
    ll personToKey = abs(person - key);
    ll keyToOffice = abs(key - office);
    return personToKey + keyToOffice;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k, p;  
    cin >> n >> k >> p;  
    vector<ll> people(n), keys(k);

    for (int i = 0; i < n; i++) cin >> people[i];
    for (int i = 0; i < k; i++) cin >> keys[i];

    // Sorting the people and keys helps in optimal matching
    sort(people.begin(), people.end());
    sort(keys.begin(), keys.end());

    // DP table: dp[i][j] -> minimum cost to assign first `j` people using first `i` keys
    vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INF));
    dp[0][0] = 0;  // Base case: no people, no keys, cost is 0

    // DP state transition
    for (int key = 1; key <= k; key++) {
        for (int person = 0; person <= n; person++) {
            // If we don't use this key, inherit the previous state's value
            dp[key][person] = dp[key - 1][person];

            // If we assign this key to a person, compute cost
            if (person > 0) {
                dp[key][person] = min(dp[key][person],
                                      max(dp[key - 1][person - 1], findCost(people[person - 1], keys[key - 1], p)));
            }
        }
    }

    // The answer is the minimum cost to assign `n` people from `k` available keys
    cout << dp[k][n] << "\n";
    return 0;
}
