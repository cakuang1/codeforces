#include <bits/stdc++.h>
using namespace std;
using int32 = int;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;
    int n = S.size();

    // Map DNA chars to 0..3
    auto idx = [&](char c) {
        switch(c) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            default:  return 3; // 'T'
        }
    };
    static const char rev[4] = {'A','C','G','T'};

    // next_pos[i][c] = the first position >= i where S[pos]=c, or n if none
    vector<array<int32,4>> next_pos(n+1);
    for(int c = 0; c < 4; c++) {
        next_pos[n][c] = n;
    }
    for(int i = n-1; i >= 0; i--) {
        for(int c = 0; c < 4; c++) {
            next_pos[i][c] = next_pos[i+1][c];
        }
        next_pos[i][ idx(S[i]) ] = i;
    }

    // dp[i] = length of shortest string NOT a subsequence of S[i..n-1]
    vector<int32> dp(n+1);
    dp[n] = 1;  // past the end: any single char will be missing
    for(int i = n-1; i >= 0; i--) {
        int32 best = INT_MAX;
        for(int c = 0; c < 4; c++) {
            int np = next_pos[i][c];
            if(np == n) {
                // character c doesn't occur in S[i..], so string of length 1 works
                best = 1;
                break;
            } else {
                // we pay 1 for c, then need dp[np+1]
                best = min(best, 1 + dp[np+1]);
            }
        }
        dp[i] = best;
    }

    // Reconstruct one shortest missing subsequence
    string answer;
    answer.reserve(dp[0]);
    int i = 0;
    while(true) {
        // we know dp[i] is the length we need from here
        for(int c = 0; c < 4; c++) {
            int np = next_pos[i][c];
            int32 cost;
            if(np == n) {
                cost = 1;
            } else {
                cost = 1 + dp[np+1];
            }
            if(cost == dp[i]) {
                // choose this character
                answer.push_back(rev[c]);
                if(np == n) {
                    // we're done
                    cout << answer << "\n";
                    return 0;
                }
                // otherwise move past the matched c
                i = np + 1;
                break;
            }
        }
    }

    return 0;
}
