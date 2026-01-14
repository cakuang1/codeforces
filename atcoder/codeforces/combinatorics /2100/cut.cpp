#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
const int MOD = 1000000007;
 
// Function to find all occurrences of pattern t in string s using a simple search.
// (For these string sizes, this is efficient enough.)
vector<int> findOccurrences(const string &s, const string &t) {
    vector<int> occ;
    int n = s.size(), m = t.size();
    for (int i = 0; i <= n - m; i++) {
        if (s.compare(i, m, t) == 0)
            occ.push_back(i);
    }
    return occ;
}
 
// The DP state will be a pair: (minMoves, ways)
struct State {
    int moves;
    int ways;
};
 
void solve() { 
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    
    // Find all starting indices where t occurs in s.
    vector<int> occ = findOccurrences(s, t);
    int occCount = occ.size();
    
    // If there is no occurrence, then no moves are needed.
    if(occCount == 0) {
        cout << 0 << " " << 1 << "\n";
        return;
    }
    
    // dp[i] will store the optimal solution for covering occ[i...occCount-1].
    // We add one extra state dp[occCount] as the base case.
    vector<State> dp(occCount + 1, {1000000, 0}); // initialize moves with a large number
    dp[occCount] = {0, 1};  // Base: no occurrences left -> 0 moves, 1 way.
    
    // Process dp from occCount-1 down to 0.
    // For each dp[i], we consider all occurrences j (starting from i) that intersect occ[i].
    // They must satisfy: occ[j] <= occ[i] + m - 1.
    for (int i = occCount - 1; i >= 0; i--) {
        int best = 1000000;
        int ways = 0;
        // Let r be the rightmost index until which occurrences intersect occ[i].
        // They satisfy: occ[j] <= occ[i] + m - 1.
        for (int j = i; j < occCount && occ[j] <= occ[i] + m - 1; j++) {
            // When we choose the occurrence at occ[j] as our move,
            // it covers all occurrences that start before occ[j] + m.
            // Find the smallest index k such that occ[k] >= occ[j] + m.
            int nextIdx = j + 1;
            // We can use binary search since occ is sorted.
            int lo = j + 1, hi = occCount;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (occ[mid] < occ[j] + m)
                    lo = mid + 1;
                else
                    hi = mid;
            }
            nextIdx = lo;
            int candidate = 1 + dp[nextIdx].moves;
            if (candidate < best) {
                best = candidate;
                ways = dp[nextIdx].ways;
            } else if (candidate == best) {
                ways = (ways + dp[nextIdx].ways) % MOD;
            }
        }
        dp[i] = {best, ways};
    }
    
    // The answer for the entire string is dp[0].
    cout << dp[0].moves << " " << dp[0].ways % MOD << "\n";
}
 
// The main function is typically responsible for handling multiple test cases.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q;
    cin >> q;
    while(q--) {
        solve();
    }
    return 0;
}
