#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!getline(cin, s)) return 0;
    int n = s.size();

    // 1) Count frequencies
    vector<int> freq(26, 0);
    for (char c : s) {
        if (c < 'A' || c > 'Z') continue;
        freq[c - 'A']++;
    }

    // 2) Quick feasibility: no letter can appear more than ceil(n/2)
    int maxf = *max_element(freq.begin(), freq.end());
    if (maxf > (n + 1) / 2) {
        cout << "-1\n";
        return 0;
    }
    // its greater  w
    string ans;
    ans.reserve(n);
    char prev = '\0';

    for (int pos = 0; pos < n; pos++) {
        bool placed = false;
        int positions_left = n - pos - 1;

        for (int c = 0; c < 26; c++) {
            if (freq[c] == 0) continue;
            char ch = char('A' + c);
            if (ch == prev) continue;

            // try placing ch
            freq[c]--;
            // recompute max freq among remaining
            int mf = 0;
            for (int d = 0; d < 26; d++)
                mf = max(mf, freq[d]);
            // check if the tail can be arranged:
            // mf <= ceil(positions_left/2)
            if (mf <= (positions_left + 1) / 2) {
                // ok
                ans.push_back(ch);
                prev = ch;
                placed = true;
                break;
            }
            // otherwise undo and try next
            freq[c]++;
        }

        if (!placed) {
            // Should never happen because we checked initial feasibility,
            // but just in case:
            cout << "-1\n";
            return 0;
        }
    }

    cout << ans << "\n";
    return 0;
}
