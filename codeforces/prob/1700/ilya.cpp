        #include <bits/stdc++.h>
        using namespace std;

        double dp[2001][2001]; // DP table: dp[i][j] = probability of j infected at time i

        int main() {
            ios::sync_with_stdio(false);
            cin.tie(NULL);

            int n,t;
            double p;
            
            cin >> n >> p >> t;


            // Base case: At time 0, all people are uninfected
            dp[0][n] = 1.0;

            // DP transitions
            for (int i = 1; i <= t; i++) {
                for (int j = 0; j <= n; j++) {
                    dp[i][j] = 0.0;

                    // Transition from state j+1 (person gets infected)
                    if (j < n) {
                        dp[i][j] += dp[i - 1][j + 1] * p;
                    }

                    // Transition from state j (person does not get infected)
                    if (j > 0) {
                        dp[i][j] += dp[i - 1][j] * (1 - p);
                    }
                }
            }

            // Compute the expected number of infected people at time t
            double result = 0.0;
            for (int i = 1; i <= n; i++) {
                result += i * dp[t][i];
            }
            
            double act = n -result;

            cout << fixed << setprecision(10) << act << "\n";

            return 0;
        }
