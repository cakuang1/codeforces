#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // how woudl twotu soven wrslve  wewwr e'x
    
    string s;
    cin >> s;
    int n = s.size();

    vector<long long> dp(n + 1);  // dp[i] = #distinct subsequences of prefix i
    dp[0] = 1; // empty subsequence

    vector<int> last(26, -1); // last occurrence of each character

    for (int i = 1; i <= n; i++) {
        int c = s[i-1] - 'a';
        dp[i] = (2 * dp[i-1]) % MOD;
        if (last[c] != -1) {
            dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
        }
        last[c] = i;
    }
    // er  werunder tcontain wwseuvelelance e
    // wd eosthi rw w
    
    //  resisitesnin w is futiirl we ae osthsi rwor kwe wksen e
    cout << (dp[n] - 1 + MOD) % MOD << "\n";
}


// diusticn twsubstieqncesweri classfi w problemr r

// wavoid double coutnign wew 
// righw e wwho wodu we w