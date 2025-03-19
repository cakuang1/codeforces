#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1e9;
 
// We'll sieve primes up to 60.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // --- Sieve of Eratosthenes up to 60 ---
    int N_limit = 60;
    vector<bool> isPrime(N_limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= N_limit; i++){
        if (isPrime[i]){
            for (int j = i * i; j <= N_limit; j += i)
                isPrime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= N_limit; i++){
        if (isPrime[i])
            primes.push_back(i);
    }
    // s = number of primes we consider (primes in range [2, 60])
    int s = primes.size(); // should be 17 for numbers up to 60.
    
    // --- Precompute the prime factor bitmask for each candidate number from 1 to 60 ---
    // We'll store the bitmask in an array fact, where fact[k] represents the set of primes dividing k.
    // Note: For k = 1, there are no prime factors.
    vector<int> fact(61, 0);
    fact[1] = 0; // 1 has no prime factors.
    for (int i = 2; i <= 60; i++){
        int bm = 0;
        for (int j = 0; j < s; j++){
            if(i % primes[j] == 0){
                bm |= (1 << j);
            }
        }
        fact[i] = bm;
    }
    
    // --- Read Input ---
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    // --- DP Setup ---
    // Let dp[i][mask] be the minimal cost for choosing b1, ..., b_i such that the union
    // of prime factors used (from the chosen b's) is exactly 'mask'.
    int maskSize = (1 << s);
    vector<vector<int>> dp(n + 1, vector<int>(maskSize, INF));
    // For reconstruction, store the chosen candidate and previous mask.
    vector<vector<int>> choice(n + 1, vector<int>(maskSize, -1));
    vector<vector<int>> par(n + 1, vector<int>(maskSize, -1));
    
    // Base state: no numbers chosen and no primes used.
    dp[0][0] = 0;
    
    // --- DP Transitions ---
    // Process the sequence one element at a time.
    for (int i = 1; i <= n; i++){
        // Try every candidate number k from 1 to 60 for b_i.
        for (int k = 1; k <= 60; k++){
            int cost = abs(arr[i - 1] - k);
            int maskForK = fact[k];
            // We can only use candidate k if none of its prime factors are already used.
            // Let x be the bitmask of primes that are "free" (not in k).
            int x = (~maskForK) & ((1 << s) - 1);
            // Enumerate all subsets 'sub' of x.
            // Any state 'sub' satisfies sub & maskForK == 0.
            for (int sub = x; ; sub = (sub - 1) & x) {
                // If state 'sub' was reachable in dp[i-1]
                if (dp[i - 1][sub] != INF) {
                    int newMask = sub | maskForK;
                    if (dp[i - 1][sub] + cost < dp[i][newMask]) {
                        dp[i][newMask] = dp[i - 1][sub] + cost;
                        choice[i][newMask] = k; // choose candidate k for position i
                        par[i][newMask] = sub;  // previous mask was 'sub'
                    }
                }
                if (sub == 0) break;
            }
        }
    }
    
    // --- Retrieve the Best Answer ---
    int best = INF, bestMask = -1;
    for (int m = 0; m < maskSize; m++){
        if (dp[n][m] < best) {
            best = dp[n][m];
            bestMask = m;
        }
    }
    
    // Reconstruct the sequence b from the DP states.
    vector<int> ans(n);
    int curMask = bestMask;
    for (int i = n; i >= 1; i--){
        ans[i - 1] = choice[i][curMask];
        curMask = par[i][curMask];
    }
    
    // --- Output the Key Sequence ---
    // (Any optimal sequence is acceptable.)
    for (int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}


 

//   