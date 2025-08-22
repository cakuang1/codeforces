#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    int mx = 1;
    for (int &x : A) { cin >> x; mx = max(mx, x); }
    for (int &x : B) { cin >> x; mx = max(mx, x); }

    // 1) SPF sieve up to mx
    vector<int> spf(mx+1, 0);
    for (int i = 2; i*i <= mx; i++) {
        if (!spf[i]) {
            for (int j = i*i; j <= mx; j += i)
                if (!spf[j]) spf[j] = i;
        }
    }
    for (int i = 2; i <= mx; i++)
        if (!spf[i]) spf[i] = i;

    // 2) Factor all A[] and B[], tally exponents
    unordered_map<int,ll> cntA, cntB;
    cntA.reserve(n*3);
    cntB.reserve(m*3);

    vector<vector<pair<int,int>>> fA(n), fB(m);
    auto factor = [&](int x, vector<pair<int,int>> & out, unordered_map<int,ll> & cnt){
        while (x > 1) {
            int p = spf[x], c = 0;
            while (x % p == 0) {
                x /= p;
                c++;
            }
            out.emplace_back(p,c);
            cnt[p] += c;
        }
    };
    for (int i = 0; i < n; i++)
        factor(A[i], fA[i], cntA);
    for (int j = 0; j < m; j++)
        factor(B[j], fB[j], cntB);

    // 3) Compute common exponents per prime
    unordered_map<int,ll> common;
    common.reserve(cntA.size());
    for (auto & [p, aexp] : cntA) {
        auto it = cntB.find(p);
        if (it != cntB.end()) {
            common[p] = min(aexp, it->second);
        }
    }

    // We'll remove from A using commonA, and from B using commonB
    auto commonA = common;
    auto commonB = common;

    // 4) Reconstruct reduced arrays
    vector<int> outA(n), outB(m);

    for (int i = 0; i < n; i++) {
        ll val = 1;
        for (auto & [p, e] : fA[i]) {
            ll rem = min<ll>(e, commonA[p]);
            commonA[p] -= rem;
            int keep = e - rem;
            for (int t = 0; t < keep; t++)
                val *= p;  // stays ≤ original A[i] ≤ 1e7
        }
        outA[i] = int(val);
    }
    for (int j = 0; j < m; j++) {
        ll val = 1;
        for (auto & [p, e] : fB[j]) {
            ll rem = min<ll>(e, commonB[p]);
            commonB[p] -= rem;
            int keep = e - rem;
            for (int t = 0; t < keep; t++)
                val *= p;
        }
        outB[j] = int(val);
    }

    // 5) Output
    cout << n << " " << m << "\n";
    for (int x : outA) cout << x << " ";
    cout << "\n";
    for (int x : outB) cout << x << " ";
    cout << "\n";
    return 0;
}
