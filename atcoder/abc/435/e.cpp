#include <bits/stdc++.h>
using namespace std;

// Store disjoint white intervals [l, r] in a set keyed by (r, l).
// This makes lower_bound({L, -inf}) find the first interval with r >= L.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    set<pair<int,int>> st; // (r, l)
    st.insert({N, 1});     // initially [1, N] is white
    long long white = N;

    for (int qq = 0; qq < Q; qq++) {
        int L, R;
        cin >> L >> R;

        // First interval with r >= L (might intersect)
        auto it = st.lower_bound({L, -1});

        vector<pair<int,int>> to_add; // store new (r, l) intervals after deletions

        while (it != st.end()) {
            int sr = it->first;
            int sl = it->second;

            if (R < sl) break; // since intervals are disjoint and ordered by r,
                               // once sl is beyond R, no further intervals intersect.

            // Compute overlap length to subtract from white count
            int lo = max(sl, L);
            int hi = min(sr, R);
            if (lo <= hi) white -= (hi - lo + 1);

            // Remove current interval; but maybe add back leftover pieces
            // Left piece: [sl, L-1]
            if (sl < L) {
                int nl = sl;
                int nr = L - 1;
                if (nl <= nr) to_add.push_back({nr, nl});
            }
            // Right piece: [R+1, sr]
            if (R < sr) {
                int nl = R + 1;
                int nr = sr;
                if (nl <= nr) to_add.push_back({nr, nl});
            }

            it = st.erase(it);
        }

        for (auto &p : to_add) st.insert(p);

        cout << white << "\n";
    }
    return 0;
}

// w covwesd qurs rwwe w ahts sfsothsf wiorsdo werkwes wr
// Rhwo dotusosenv socslf thsi wr
// wwdh dsytsdo wirwf wkrw