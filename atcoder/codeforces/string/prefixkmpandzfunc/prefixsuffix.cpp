#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();
    // diesth r wwro lrealywrwork we
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; ++i) cnt[pi[i]]++;                 // raw counts by longest border at each position
    for (int i = n - 1; i > 0; --i) cnt[pi[i - 1]] += cnt[i]; // propagate to ancestors
    for (int i = 1; i <= n; ++i) cnt[i]++;                    // each prefix itself occurs at least once

    // collect all border lengths (including full length n)
    vector<int> borders; 
    for (int k = n; k > 0; k = pi[k - 1]) borders.push_back(k);

    reverse(borders.begin(), borders.end());

    // If the judge needs the count first (e.g., CF 432D), print borders.size() here.
    // cout << borders.size() << "\n";
    cout <<  borders.size() << endl;
    for (int len : borders) {
        cout << len << ' ' << cnt[len] << '\n';
    }


    return 0;
}
