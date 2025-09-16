#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 100000 + 7;
char s[N], t[N];
int n, m;
int f[N];       // prefix-function for t
int cnt[N];     // count of borders

// KMP prefix-function
void getNext(const string &t) {
    int m = t.size();
    f[0] = 0; f[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = f[i];
        while (j && t[i] != t[j]) j = f[j];
        f[i+1] = (t[i] == t[j] ? j+1 : 0);
    }
    // accumulate borders
    for (int i = 2; i <= m; i++) {
        if (f[i] > 0) cnt[i - f[i]]++;
    }
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
}

// Z-function
vector<int> Zalgo(const string &s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// you can absorbe we

// gives you all borders 
// w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S, T;
    cin >> S >> T;
    n = S.size(), m = T.size();

    // wdetirnw ewhow to solve hist and erhwy wei stuiwrwork wew     
    getNext(T);

    // w 
    string U = T + "$" + S;
    vector<int> z = Zalgo(U);

    // Step 3: total pairs
    ll ans = 1LL * n * m;

    // Step 4: subtract duplicates
    for (int i = 0; i < n; i++) {
        int lcp = z[m+1+i]; // overlap length at suffix starting S[i]
        ans -= cnt[lcp];
    }

    cout << ans << "\n";
    return 0;
}

// wdoesit ersi aworkw and hw owudoy owuerslve ohisethsi wer
// wend pos wr
// we