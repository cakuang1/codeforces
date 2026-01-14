#include <bits/stdc++.h>
using namespace std;

vector<int> lis_indices(const vector<int>& a) {
    int n = a.size();
    vector<int> d, d_idx, prev(n, -1);
    d.reserve(n);
    d_idx.reserve(n);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        auto it = lower_bound(d.begin(), d.end(), x);
        int pos = it - d.begin();
        if (it == d.end()) {
            d.push_back(x);
            d_idx.push_back(i);
        } else {
            *it = x;
            d_idx[pos] = i;
        }
        if (pos > 0) prev[i] = d_idx[pos - 1];
    }
    // reconstruct
    vector<int> seq;
    int k = d.size();
    seq.reserve(k);
    int cur = d_idx[k - 1];
    while (cur != -1) {
        seq.push_back(cur);
        cur = prev[cur];
    }
    reverse(seq.begin(), seq.end());
    return seq;  // indices in [0..n)
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    // 1) find LIS of p
    vector<int> I = lis_indices(p);
    int k = I.size();

    // 2) find length of LDS of p by LIS on q = n+1-p
    vector<int> q(n);
    for (int i = 0; i < n; i++) {
        q[i] = n + 1 - p[i];
    }
    vector<int> fullLds = lis_indices(q);
    int l = fullLds.size();

    // feasibility
    if (k + l > n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // mark LIS positions
    vector<char> used(n, 0);
    for (int idx : I) used[idx] = 1;

    // build remaining sequence
    vector<int> remP, remIdx;
    remP.reserve(n - k);
    remIdx.reserve(n - k);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            remP.push_back(p[i]);
            remIdx.push_back(i);
        }
    }
    // compute LDS on remP by LIS on rq = max+1 - remP
    int m = remP.size();
    vector<int> rq(m);
    for (int i = 0; i < m; i++) {
        rq[i] = n + 1 - remP[i];
    }
    vector<int> Jrem = lis_indices(rq);
    // map back to original indices
    vector<int> J;
    J.reserve(l);
    for (int pos : Jrem) {
        J.push_back(remIdx[pos]);
    }

    // output
    cout << k << "\n";
    for (int idx : I) cout << (idx+1) << " ";
    cout << "\n";

    cout << l << "\n";
    for (int idx : J) cout << (idx+1) << " ";
    cout << "\n";
    return 0;
}
 

/ 