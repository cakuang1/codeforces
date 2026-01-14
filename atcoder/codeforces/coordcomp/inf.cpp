#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fenwick (BIT) for inversion counting
struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int _n): n(_n), f(n,0) {}
    void update(int i, ll v){
        for(; i<n; i |= i+1) f[i]+=v;
    }
    ll query(int i) const {
        ll s=0;
        for(; i>=0; i=(i&(i+1))-1) s+=f[i];
        return s;
    }
    // sum on [l..r]
    ll range(int l, int r) const {
        if(l>r) return 0;
        return query(r) - (l?query(l-1):0);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    map<ll,ll> M;
    // Perform the swaps, but only store mappings for touched positions
    for(int i = 0; i < q; i++){
        ll p1, p2;
        cin >> p1 >> p2;
        --p1; --p2;  // make 0-based
        ll v1 = M.count(p1) ? M[p1] : p1;
        ll v2 = M.count(p2) ? M[p2] : p2;
        M[p1] = v2;
        M[p2] = v1;
    }

    // Extract the resulting (pos -> val) pairs, sorted by pos
    int n = M.size();
    vector<pair<ll,ll>> A;
    A.reserve(n);
    for(auto &pr : M){
        A.emplace_back(pr.first, pr.second);
    }

    // Build array B of the final values in that order
    vector<ll> B(n);
    for(int i = 0; i < n; i++){
        B[i] = A[i].second;
    }

    // Coordinate‐compress B so we can fenwick‐count inversions
    vector<ll> comp = B;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(int i = 0; i < n; i++){
        B[i] = int(lower_bound(comp.begin(), comp.end(), B[i]) - comp.begin());
    }

    // Count inversions in B: number of pairs i<j with B[i]>B[j]
    Fenwick fw(n);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        // how many seen so far are > B[i] ?
        ans += fw.range(B[i]+1, n-1);
        fw.update(B[i], 1);
    }
    
    // Build a map from original pos to its index in A[]
    unordered_map<ll,int> idx;
    idx.reserve(n*2);
    for(int i = 0; i < n; i++){
        idx[A[i].first] = i;
    }

    // Finally, add the “distance” corrections:
    // sum over each final position i of:
    //   abs(origPos - mappedPos) - abs(i - beforeIndex)
    for(int i = 0; i < n; i++){
        ll origPos   = A[i].first;
        ll mappedPos = A[i].second;
        int beforeIndex = idx[mappedPos];
        ans += ll(abs(origPos - mappedPos)) 
             - ll(abs(i - beforeIndex));
    }

    cout << ans << "\n";
    return 0;
}

//  natural positions 