#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Build suffix array in O(n log n)
vector<int> build_sa(const string &s) {
    int n = s.size(), N = max(256, n) + 1;
    vector<int> sa(n), rnk(n), tmp(n), cnt(N);
    for (int i = 0; i < n; i++) sa[i] = i, rnk[i] = s[i];
    for (int k = 1;; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
            int ri = i + k < n ? rnk[i + k] : -1;
            int rj = j + k < n ? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);
        rnk = tmp;
        if (rnk[sa[n-1]] == n-1) break;
    }
    return sa;
}

// Kasai algorithm: build LCP array in O(n)
vector<int> build_lcp(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n-1);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] > 0) {
            int j = sa[rank[i] - 1];
            while (i+h<n && j+h<n && s[i+h]==s[j+h]) h++;
            lcp[rank[i]-1] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}




// tae wrkw the occ we pwe
///  o cc wpew wer
// wetwher wrdo eshitrealy erow kweadm wewg werdoesht iw orkw 
// 


// p occurs wastw ebot e 
// wgiven wtwtwo postiosn we 
// fond w 

// LCP 
// P occurs at both i ad jwermeans w


// i = 2 wj = 6 er



//  take every subtsring p wercount how amn wer 
// this is exactly we w

// tak  evetyw e werw
//  wtrper w wer
// wp wrmsitw abe a preixa bot suffixes we


// woccurncesww fo wew we
// triples e wew 
// niubmer of triples p i werj wer



// wsumwrof subsraray wermin. ww e
// so take wrthe min wewa w 
// detmerin wew hwo wt solve htis wrand why we
// longest ecp weommon rpefix wr wsfufix we wer
// suffxi we0 we

// LCP w*() sfufxi we  w
// SUFXIX we ww erw
//  werultimate erly wrthe we  

// lcp wrwis. whatwew

// How to sum mins over all siarays win O () w

// sm of susbraray werminima w
//  
// sufuxie fodred erby wethesfufa r aray sa w, weTHE Lc pw
// swap orderings wor this we weww

// this wis aonyl we


// wwtw s thw suffxi wes wewthw eo sti we
// wlc pwer weis wha trand wow we to solve htis wr

/// @brief  w
/// @param lcp 
/// @return 

// inne  wer
long long sum_lcp_pairs(const vector<int> &lcp) {
    int n = lcp.size();
    vector<int> L(n), R(n);
    stack<int> st;
    // previous less
    for (int i = 0; i < n; i++) {
        while (!st.empty() && lcp[st.top()] >= lcp[i]) st.pop();
        L[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    // next less
    for (int i = n-1; i >= 0; i--) {
        while (!st.empty() && lcp[st.top()] > lcp[i]) st.pop();
        R[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll left = i - L[i];
        ll right = R[i] - i;
        res += 1LL * lcp[i] * left * right;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int n = s.size();
        auto sa = build_sa(s);
        auto lcp = build_lcp(s, sa);

        // sum of suffix lengths = n*(n+1)/2
        ll total = 1LL * n * (n+1) / 2;

        // add 2 * sum of all pairwise LCPs
        total += 2 * sum_lcp_pairs(lcp);

        cout << total << "\n";
    }
}
