#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Hull {
    vector<ll> m, c, xs;
    vector<int> idx;

    void build(const vector<tuple<ll,ll,int>>& lines) {
        auto tmp = lines;
        sort(tmp.begin(), tmp.end(), [&](auto &A, auto &B){
            ll ma = get<0>(A), mb = get<0>(B);
            ll ca = get<1>(A), cb = get<1>(B);
            if (ma != mb) return ma < mb;
            return ca > cb;  // same slope, larger intercept first
        });
        m.clear(); c.clear(); xs.clear(); idx.clear();
        for (auto &[mv, cv, vi] : tmp) {
            if (!m.empty() && mv == m.back())
                continue;  // skip worse duplicate slope

            while (!m.empty()) {
                long double x = (long double)(cv - c.back()) / (m.back() - mv);
                if (x <= xs.back()) {
                    m.pop_back(); c.pop_back(); idx.pop_back(); xs.pop_back();
                } else break;
            }

            if (m.empty()) {
                xs.push_back(LLONG_MIN);
            } else {
                long double x = (long double)(cv - c.back()) / (m.back() - mv);
                xs.push_back((ll)floor(x));
            }

            m.push_back(mv);
            c.push_back(cv);
            idx.push_back(vi);
        }
    }

    pair<ll,int> query(ll t) const {
        int j = int(upper_bound(xs.begin(), xs.end(), t) - xs.begin() - 1);
        return { m[j]*t + c[j], idx[j] };
    }
};

static const int MAXN = 100000;
int n, q;
vector<ll> a, bval;
vector<tuple<ll,ll,int>> segLines[4*MAXN];
vector<Hull> segHull;

// SEGMENT-TREE BUILD
void build(int p, int L, int R) {
    if (L == R) {
        segLines[p].push_back({ bval[L], a[L], L });
    } else {
        int M = (L + R) >> 1;
        build(p<<1,   L,   M);
        build(p<<1|1, M+1, R);
        auto &Lvec = segLines[p<<1];
        auto &Rvec = segLines[p<<1|1];
        auto &V    = segLines[p];
        V.reserve(Lvec.size() + Rvec.size());
        V.insert(V.end(), Lvec.begin(), Lvec.end());
        V.insert(V.end(), Rvec.begin(), Rvec.end());
    }
    // Now build the hull at this node
    segHull[p].build(segLines[p]);
}

// SEGMENT-TREE QUERY
pair<ll,int> query(int p, int L, int R, int i, int j, ll t) {
    if (j < L || R < i) return { LLONG_MIN, -1 };
    if (i <= L && R <= j) {
        return segHull[p].query(t);
    }
    int M = (L + R) >> 1;
    auto left  = query(p<<1,   L,   M, i, j, t);
    auto right = query(p<<1|1, M+1, R, i, j, t);
    return (left.first >= right.first ? left : right);
}

// located erin the tial of the train we ww an wehow ol 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // wer  wudne rstnad wrhte high we
    cin >> n >> q;
    a   .assign(n+1, 0);
    bval.assign(n+1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> bval[i];
    
    segHull.assign(4*(n+1), Hull());
    // build lines into segLines, then hulls
    build(1, 1, n);

    while (q--) {
        int l, r; ll t;
        cin >> l >> r >> t;
        auto ans = query(1, 1, n, l, r, t);
        cout << ans.second << "\n";
    }
    return 0;
}
