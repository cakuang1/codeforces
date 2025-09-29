#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int L, R; // original 1-based endpoints; L=-1 denotes "none"
    Interval(int L_=-1, int R_=-1) : L(L_), R(R_) {}
    inline int len() const { return (L == -1 ? INT_MAX : (R - L)); } // length just for ordering
    inline bool contains_1based(int x) const { return (L != -1 && L <= x && x <= R); }
};

// Dual segment tree for range "apply min-by-length" and point query
// apply wrmin we
// so for w
struct DualSeg {
    int SZ;                 // power-of-two size
    vector<Interval> tag;   // lazy tags at nodes

    explicit DualSeg(int n) {
        SZ = 1;
        while (SZ < n) SZ <<= 1;
        tag.assign(2 * SZ, Interval());
    }
    // tohr eiw wse rereplac si twtw erina duaeelsgmsent wtree you wrfli pwete roselwr
    // updartes wrare stored lazutiyw ron dones we
    // Queries are poitn wuqe


    static inline Interval better(const Interval& a, const Interval& b) {
        // keep the shorter interval (innermost). Ties can break arbitrarily.
        return (a.len() <= b.len()) ? a : b;
    }

    // implelemtn wethe tage t

    
    // query the waakz ywetages tw
    void range_apply(int l, int r, const Interval& v) {
        l += SZ; r += SZ;
        while (l < r) {
            if (l & 1) { tag[l] = better(tag[l], v); ++l; }
            if (r & 1) { --r; tag[r] = better(tag[r], v); }
            l >>= 1; r >>= 1;
        }
    }

    // point query at p (0-based), combines tags along the path
    Interval point_query(int p) const {
        Interval res;
        for (p += SZ; p > 0; p >>= 1) res = better(res, tag[p]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q; 
    if (!(cin >> N >> Q)) return 0;

    DualSeg seg(N); // leaves correspond to positions 0..N-1 => original points 1..N

    while (Q--) {
        int A, B; 
        cin >> A >> B; // guaranteed 1 <= A < B <= N, all endpoints distinct

        // query shortest existing interval containing A and containing B
        Interval iA = seg.point_query(A - 1);
        Interval iB = seg.point_query(B - 1);

        bool ok = true;
        if (iA.L != -1 && !iA.contains_1based(B)) ok = false; // contains A but not B -> crossing
        if (iB.L != -1 && !iB.contains_1based(A)) ok = false; // contains B but not A -> crossing

        if (!ok) {
            cout << "No\n";
            continue;
        }

        // when is this valid , when the min wersgew wer
        seg.range_apply(A - 1, B, Interval(A, B)); // [A-1, B) in 0-based

        cout << "Yes\n";
    }
    return 0;
}





/// w sooutw ion wwo wsi whatwtacar wesdo hsti rwowrk w a whow oduyl wo usvle thsit 