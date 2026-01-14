#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Block {
    ll len;
    char c;
};

// Merge adjacent blocks with the same character
vector<Block> read_blocks(int n) {
    vector<Block> res;
    for (int i = 0; i < n; i++) {
        string token;
        cin >> token; // format: len-char
        int dash = token.find('-');
        ll len = stoll(token.substr(0, dash));
        char c = token[dash + 1];

        if (!res.empty() && res.back().c == c) {
            res.back().len += len;
        } else {
            res.push_back({len, c});
        }
    }
    return res;
}

// KMP prefix function for block sequences
vector<int> prefix_function(const vector<Block> &pat) {
    int m = (int)pat.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && (pat[i].c != pat[j].c || pat[i].len != pat[j].len))
            j = pi[j - 1];
        if (pat[i].c == pat[j].c && pat[i].len == pat[j].len) j++;
        pi[i] = j;
    }
    return pi;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Block> text = read_blocks(n);
    vector<Block> pat = read_blocks(m);

    n = (int)text.size();
    m = (int)pat.size();
    ll ans = 0;

    if (m == 1) {
        // Case 1: single block pattern
        for (auto &blk : text) {
            if (blk.c == pat[0].c && blk.len >= pat[0].len) {
                ans += blk.len - pat[0].len + 1;
            }
        }
    } else if (m == 2) {
        // Case 2: two block pattern
        for (int i = 0; i + 1 < n; i++) {
            if (text[i].c == pat[0].c && text[i].len >= pat[0].len &&
                text[i + 1].c == pat[1].c && text[i + 1].len >= pat[1].len) {
                ans++;
            }
        }
    } else {
        // Case 3: m >= 3
        // Extract middle part of pattern
        vector<Block> mid(pat.begin() + 1, pat.end() - 1);

        // Build sequence for KMP: mid + delimiter + text
        vector<Block> combined = mid;
        combined.push_back({-1, '#'}); // delimiter
        for (auto &blk : text) combined.push_back(blk);

        // KMP on blocks
        vector<int> pi = prefix_function(combined);
        int M = (int)mid.size();

        for (int i = 0; i < (int)combined.size(); i++) {
            if (pi[i] == M) {
                // Found mid match ending at text index `end`
                int end = i - 2 * M;
                int start = end - M + 1;

                if (start - 1 >= 0 && end + 1 < n) {
                    if (text[start - 1].c == pat[0].c && text[start - 1].len >= pat[0].len &&
                        text[end + 1].c == pat[m - 1].c && text[end + 1].len >= pat[m - 1].len) {
                        ans++;
                    }
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}