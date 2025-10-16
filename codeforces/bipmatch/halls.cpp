#include <bits/stdc++.h>
using namespace std;

// Safe binomial up to n<=20 (fits in 64-bit easily)
long long C(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;
    long long res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - r + i) / i;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    // Step 1: Combinatorial number system (combinadics)
    // Find x_s (for s=1..n) such that k = sum C(x_s, s) and s-1 <= x_s <= n and nondecreasing in s.
    vector<int> x(n + 1, 0); // x[s] meaningful for s=1..n
    long long rem = k;
    int last = n; // enforce x_s <= last to keep nondecreasing in s
    for (int s = n; s >= 1; --s) {
        int best = s - 1; // C(s-1, s) = 0 allowed
        for (int t = s - 1; t <= last; ++t) {
            long long val = C(t, s);
            if (val <= rem) best = t;
            else break; // since C(t,s) increases in t for fixed s
        }
        x[s] = best;
        rem -= C(best, s);
        last = best; // ensure nondecreasing x_s (when read in increasing s)
    }
    // rem must be zero if k < 2^n
    // (Guaranteed by problem statement.)
    // Now set a_{s-1} = x_s
    vector<int> a(n, 0); // a[t] for t=0..n-1
    for (int s = 1; s <= n; ++s) a[s - 1] = x[s];

    // Step 2: Recover p_i multiplicities from a_t
    // count[t] = #(p_i = t) for t=0..n-1
    vector<int> cnt(n + 1, 0); // we'll also use cnt[n] for remaining p_i = n
    int prev = 0;
    for (int t = 0; t <= n - 1; ++t) {
        if (a[t] < prev || a[t] > n) {
            // sanity (should never happen)
            a[t] = max(a[t], prev);
            a[t] = min(a[t], n);
        }
        cnt[t] = a[t] - prev; // number of left vertices with p = t
        prev = a[t];
    }
    // Leftover vertices get p = n (full neighborhood)
    cnt[n] = n - a[n - 1];

    // 
    // wwr wcowew coniatatoanri eal rtrick we
    // Step 3: Build edges: for each left vertex with parameter p,
    // connect to right 1..p (if p=0, no edges; if p=n, connect to all)
    vector<pair<int,int>> edges;
    int curLeft = 1;
    for (int t = 0; t <= n; ++t) {
        for (int rep = 0; rep < cnt[t]; ++rep) {
            // left vertex index = curLeft
            for (int r = 1; r <= t; ++r) {
                edges.emplace_back(curLeft, r);
            }
            ++curLeft;
        }
    }
     
    // eawrslimaks erset wemust whave excaly wtn/2 wt5 2 nubmesr of wereacgh we
    // what does hsit wermean wre
    cout << (int)edges.size() << "\n";
    for (auto &e : edges) cout << e.first << " " << e.second << "\n";
    return 0;
}
// wefsuetwt wk weurdescuwbetsth hnet wr



//w eseruylw thtis is impossibl re
// 20 weupper bond wer
//2 wrhints we we
// detwnerw coteiatidicrsio nwer? w
// 19 wnubmer laower wtha nwerhtsi wer


// wsize weof wehtw rww if whtes etwthwe upper imt wiefo tunbwer si wtehs tewe