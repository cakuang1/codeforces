#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*** Suffix Array (doubling with counting sort): O(n log n) ***/
vector<int> build_sa(const string &s) {
    int n = (int)s.size();
    vector<int> sa(n), rnk(n), tmp(n), sa2(n), cnt(max(256, n) + 1, 0);
    for (int i = 0; i < n; ++i) rnk[i] = (unsigned char)s[i], sa[i] = i;

    for (int k = 1; k < n; k <<= 1) {
        // sort by second key (i+k)
        fill(cnt.begin(), cnt.begin() + max(256, n) + 1, 0);
        for (int i = 0; i < n; ++i) {
            int key = (i + k < n ? rnk[i + k] + 1 : 0);
            ++cnt[key];
        }
        for (int i = 1; i < (int)cnt.size(); ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int idx = sa[i];
            int key = (idx + k < n ? rnk[idx + k] + 1 : 0);
            sa2[--cnt[key]] = idx;
        }
        // sort by first key (i)
        fill(cnt.begin(), cnt.begin() + max(256, n) + 1, 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i] + 1];
        for (int i = 1; i < (int)cnt.size(); ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int idx = sa2[i];
            sa[--cnt[rnk[idx] + 1]] = idx;
        }
        // re-rank
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int a = sa[i - 1], b = sa[i];
            int ra1 = rnk[a], rb1 = rnk[b];
            int ra2 = (a + k < n ? rnk[a + k] : -1);
            int rb2 = (b + k < n ? rnk[b + k] : -1);
            tmp[b] = tmp[a] + (ra1 != rb1 || ra2 != rb2);
        }
        rnk.swap(tmp);
        if (rnk[sa.back()] == n - 1) break;
    }
    return sa;
}

/*** Kasai LCP: O(n) ***/
vector<int> build_lcp(const string &s, const vector<int> &sa) {
    int n = (int)s.size();
    vector<int> rnk(n), lcp(max(0, n - 1), 0);
    for (int i = 0; i < n; ++i) rnk[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; ++i) {
        int ri = rnk[i];
        if (ri == 0) { h = 0; continue; }
        int j = sa[ri - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
        lcp[ri - 1] = h;
        if (h) --h;
    }
    return lcp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string s, t;
    cin >> s >> t;

    // Edge: if all end positions are forbidden, answer is 0.
    bool any_allowed_end = false;
    for (char c : t) if (c == '0') { any_allowed_end = true; break; }
    if (!any_allowed_end) { cout << 0 << "\n"; return 0; }

    // Reverse s only (forbidden END -> forbidden START).
    reverse(s.begin(), s.end());

    // Map start j in s_rev -> original end at (n-1-j).
    vector<int> goodStart(n, 0);
    for (int j = 0; j < n; ++j) {
        goodStart[j] = (t[n - 1 - j] == '0');
    }

    // Suffix array + LCP on s_rev.
    auto sa = build_sa(s);
    auto lcp = build_lcp(s, sa);

    // Prefix sums of allowed suffixes in SA order.
    vector<int> pref(n, 0);
    for (int i = 0; i < n; ++i) {
        pref[i] = goodStart[sa[i]] + (i ? pref[i - 1] : 0);
    }
    auto range_count = [&](int L, int R) -> int {
        if (L > R) return 0;
        return pref[R] - (L ? pref[L - 1] : 0);
    };

    // Case f(a) = 1: longest suffix at a good start.
    ll best = 0;
    for (int j = 0; j < n; ++j) if (goodStart[j]) {
        best = max(best, (ll)(n - j));
    }

    // Case f(a) > 1: process each LCP with stack trick.
    int m = (int)lcp.size();
    if (m > 0) {
        vector<int> L(m), R(m);
        // Previous strictly smaller
        {
            stack<int> st;
            for (int i = 0; i < m; ++i) {
                while (!st.empty() && lcp[st.top()] >= lcp[i]) st.pop();
                L[i] = st.empty() ? -1 : st.top();
                st.push(i);
            }
        }
        // Next smaller (strict)
        {
            stack<int> st;
            for (int i = m - 1; i >= 0; --i) {
                while (!st.empty() && lcp[st.top()] > lcp[i]) st.pop();
                R[i] = st.empty() ? m : st.top();
                st.push(i);
            }
        }
        for (int i = 0; i < m; ++i) if (lcp[i] > 0) {
            int leftSA  = L[i] + 1;
            int rightSA = R[i]; // inclusive
            int cnt = range_count(leftSA, rightSA);
            if (cnt > 0) {
                ll cand = 1LL * lcp[i] * cnt;
                best = max(best, cand);
            }
        }
    }
    
    cout << best << "\n";
    return 0;
}
