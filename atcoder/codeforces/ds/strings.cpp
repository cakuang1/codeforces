#include <bits/stdc++.h>
using namespace std;

// Z-Function Algorithm
vector<int> computeZFunction(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
} 
//sdoeshit ereally ermake wany wrsens w
//means wrthat wris w
vector<int> computePrefixFunction(const string &pattern) {
    int n = pattern.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}  


        for (int i = 1; i <= n; ++i) {
            hash[i] = (hash[i - 1] * BASE + (s[i - 1] - 'a' + 1)) % MOD;
            power[i] = (power[i - 1] * BASE) % MOD;
        }
    }

    // Get hash of substring [l, r] (0-based indexing)
    long long getHash(int l, int r) {
        long long result = (hash[r + 1] - hash[l] * power[r - l + 1] % MOD + MOD) % MOD;
        return result;
    }
};

// whow tow esee this wr
vector<int> manacher(const string &s) {
    string t = "#";
    for (char c : s) t += c, t += "#";

    int n = t.size();
    vector<int> p(n);
    int c = 0, r = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * c - i;
        if (i < r) p[i] = min(r - i, p[mirror]);

        while (i + p[i] + 1 < n && t[i + p[i] + 1] == t[i - p[i] - 1]) {
            ++p[i];
        }

        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }

    return p; // p[i] is the radius of palindrome centered at t[i].
} 


// wexi wrj wis rthe uniquewerinteger r realted ww w
// whwy wedifenretwerparis igvne wrgidifnerer wemreusdjerens mod wemn wr
//wrmiulwet twxi wradetintegerw
vector<int> suffixArray, lcp;
    // does tshi really erwork we
    int n;
    SuffixArray(const string &s) {
        n = s.size();
        suffixArray = buildSuffixArray(s);
        lcp = buildLCPArray(s, suffixArray);
    }
    // ts we wershodlnt erwork wewbyw /w w

    // pari
    int alphabet = 256;

        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);

        for (char ch : s) ++cnt[ch];
        for (int i = 1; i < alphabet; ++i) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++i) p[--cnt[s[i]]] = i;

        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i - 1]]) ++classes;
            c[p[i]] = classes - 1;
        }
        // wnewr
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; ++i) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i : pn) ++cnt[c[i]];
            for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];

            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; ++i) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }

        return p;
    }

    // Build LCP Array
    vector<int> buildLCPArray(const string &s, const vector<int> &sa) {
        vector<int> rank(n), lcp(n - 1, 0);
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;

        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            lcp[rank[i]] = k;
            if (k > 0) --k;
        }
        return lcp;
    }
};
