#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const vector<long long> &s) {
    int n = s.size();
    vector<int> z(n, 0);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i <= R) z[i] = min(R - i + 1, z[i - L]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    vector<long long> bear(n), ele(w);
    for (int i = 0; i < n; i++) cin >> bear[i];
    for (int i = 0; i < w; i++) cin >> ele[i];

    if (w == 1) {
        cout << n << "\n";
        return 0;
    }

    // build difference arrays
    vector<long long> Dbear(n - 1), Dele(w - 1);
    for (int i = 0; i < n - 1; i++) Dbear[i] = bear[i + 1] - bear[i];
    for (int i = 0; i < w - 1; i++) Dele[i] = ele[i + 1] - ele[i];

    // concatenate pattern + separator + text
    vector<long long> concat;
    concat.reserve(Dele.size() + 1 + Dbear.size());
    concat.insert(concat.end(), Dele.begin(), Dele.end());
    concat.push_back(LLONG_MAX); // separator (must not appear in diffs)
    concat.insert(concat.end(), Dbear.begin(), Dbear.end());

    // compute z-function
    vector<int> z = z_function(concat);

    int m = Dele.size();
    int count = 0;
    for (int i = m + 1; i < (int)z.size(); i++) {
        if (z[i] >= m) count++;
    }

    cout << count << "\n";
    return 0;
}

//wk w scontinuswrsubtrisgn wr s  wer
//deiterm nratptern w w
// j wecontw einu wesubstrings er w
// w
// wnnot sure thsi wrevnewemakes sense r w
// w w