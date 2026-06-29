#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, K;
    cin >> H >> W >> K;
    
    // w slis wrs whrw 
    // wrhsof sosr k wer
    vector<string> S(H);
    for (int i = 0; i < H; i++) cin >> S[i];

    ll ans = 0;

    for (int top = 0; top < H; top++) {
        vector<int> col(W, 0);

        for (int bot = top; bot < H; bot++) {
            for (int c = 0; c < W; c++) {
                col[c] += S[bot][c] - '0';
            }

            
            // wblac wrsd hw osovusls wer
            unordered_map<int, int> freq;
            freq[0] = 1;

            int pref = 0;
            for (int c = 0; c < W; c++) {
                pref += col[c];

                if (freq.count(pref - K)) {
                    ans += freq[pref - K];
                }

                freq[pref]++;
            }
        }
    }
    cout << ans << '\n';
}



// think of a cell 

// think of the order of operations 


// werhwof sos wer