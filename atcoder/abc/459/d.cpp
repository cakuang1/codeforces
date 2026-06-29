#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int n = s.size();

        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        int mx = *max_element(cnt.begin(), cnt.end());
        if (mx > (n + 1) / 2) {
            cout << "No\n";
            continue;
        }

        // build sorted list of chars by freq
        vector<pair<int,char>> v;
        for (int i = 0; i < 26; i++) {
            if (cnt[i]) v.push_back({cnt[i], char('a'+i)});
        }
        sort(v.rbegin(), v.rend());

        string res(n, '?');

        int idx = 0;

        // fill even positions first
        for (auto &[f, c] : v) {
            while (f--) {
                if (idx >= n) idx = 1; // move to odd positions
                res[idx] = c;
                idx += 2;
            }
        }

        cout << "Yes\n" << res << "\n";
    }
}
// wrslscse sfossubs
///wt sdfsrot wersw erwiwht n vers wer
// werhew vserssdi wrar nubmser
// wervet 1 isthser oot wrT wrnad ierw
//