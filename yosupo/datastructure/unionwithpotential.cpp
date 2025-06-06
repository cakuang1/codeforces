#include <bits/stdc++.h>
using namespace std;

vector<int> parent_, rnk_;

// Find with path-compression
int find_set(int a) {
    if (parent_[a] == a) 
        return a;
    return parent_[a] = find_set(parent_[a]);
}

// Union by rank
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk_[a] < rnk_[b]) 
            swap(a, b);
        parent_[b] = a;
        if (rnk_[a] == rnk_[b]) 
            rnk_[a]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    parent_.resize(n);
    rnk_   .resize(n);
    for (int i = 0; i < n; i++) {
        parent_[i] = i;
        rnk_   [i] = 0;
    }

    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        // assume u, v are 0-based in [0..n-1]
        if (type == 0) {
            // merge the sets containing u and v
            union_sets(u, v);
        } else {
            // query: are u and v in the same set?
            if (find_set(u) == find_set(v))
                cout << "1\n";
            else
                cout << "0\n";
        }
    }

    return 0;
}
