#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

inline void addMod(int &x, int v) {
    x += v;
    if (x >= MOD) x -= MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<long long> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    
    vector<vector<int>> dp(n+1, vector<int>(K+1, 0)),
                        ndp(n+1, vector<int>(K+1, 0));

    // Base case: before using any items, i=0, j=0, z=0 => 1 way
    dp[0][0] = 1;

    long long prev = a[0];
    for(int i = 0; i < n; i++){
        // reset next‐layer
        for(int j = 0; j <= n; j++)
            fill(ndp[j].begin(), ndp[j].end(), 0);

        long long cur = a[i];
        long long diff = (i == 0 ? 0LL : cur - prev);

        // transition from dp → ndp
        for(int j = 0; j <= i; j++){
            for(int z = 0; z <= K; z++){
                int ways = dp[j][z];
                if(!ways) continue;
                // each open group accrues diff:
                long long nz = z + 1LL*j * diff;
                if(nz > K) continue;
                int iz = (int)nz;
                                
                // 1) new singleton group (open&close immediately):
                addMod(ndp[j][iz], ways);

                // 2) add to one of j open groups, keep it open:
                if(j > 0){
                    addMod(ndp[j][iz], int((1LL*ways*j) % MOD));
                }

                // 3) open a brand-new group:
                addMod(ndp[j+1][iz], ways);

                // 4) close one of the j open groups:
                if(j > 0){
                    addMod(ndp[j-1][iz], int((1LL*ways*j) % MOD));
                }
            }
        }

        // swap dp and ndp for next iteration
        dp.swap(ndp);
        prev = cur;
    }

    // answer = sum of dp[0][z] over z=0..K (all closed)
    int ans = 0;
    for(int z = 0; z <= K; z++){
        addMod(ans, dp[0][z]);
    }
    cout << ans << "\n";
    return 0;
}
