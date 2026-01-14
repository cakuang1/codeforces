using namespace std;



// wewtiwnrestns ignsersd qerseiton 

    // ws buset  istwhr wee
struct Item {
    int l1;      // inclusive start range left
    int l2;      // inclusive start range right
    int r;       // fixed right endpoint
    int val;     // OR value for any [l..r] where l in [l1..l2]
};

struct SegTreeMax {
    int n;
    vector<int> st;
    static constexpr int NEG = -1e9;

    SegTreeMax(int n_) : n(n_), st(4 * (n + 1), NEG) {}

    void build(int p, int s, int t) {
        if (s == t) {
            st[p] = (s == 0 ? 0 : NEG); // dp[0]=0, others=-inf
            return;
        }
        int m = (s + t) >> 1;
        build(p << 1, s, m);
        build(p << 1 | 1, m + 1, t);
        st[p] = max(st[p << 1], st[p << 1 | 1]);
    }

    int query(int l, int r, int p, int s, int t) {
        if (l > r) return NEG;
        if (l <= s && t <= r) return st[p];
        int m = (s + t) >> 1;
        int ans = NEG;
        if (l <= m) ans = max(ans, query(l, r, p << 1, s, m));
        if (r > m)  ans = max(ans, query(l, r, p << 1 | 1, m + 1, t));
        return ans;
    }

    void update_max(int idx, int val, int p, int s, int t) {
        if (s == t) {
            st[p] = max(st[p], val);
            return;
        }
        int m = (s + t) >> 1;
        if (idx <= m) update_max(idx, val, p << 1, s, m);
        else          update_max(idx, val, p << 1 | 1, m + 1, t);
        st[p] = max(st[p << 1], st[p << 1 | 1]);
    }
};

// w rkwrw perw=
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Sparse table for range OR query (1-indexed)
    int K = 0;
    while ((1 << (K + 1)) <= n) K++;
    vector<vector<int>> st(n + 2, vector<int>(K + 1, 0));
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int j = 1; j <= K; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = st[i][j - 1] | st[i + (1 << (j - 1))][j - 1];
        }
    }

    auto range_or = [&](int l, int r) -> int {
        int len = r - l + 1;
        int c = 31 - __builtin_clz(len); // floor(log2(len))
        return st[l][c] | st[r - (1 << c) + 1][c];
    };

    vector<Item> items;
    items.reserve((size_t)n * 32);

    int last[31] = {}; // last[bit] = last index where this bit appears (<= current r)

    for (int r = 1; r <= n; r++) {
        // Update last occurrences with a[r]
        for (int b = 0; b < 30; b++) {
            if ((a[r] >> b) & 1) last[b] = r;
        }

        // Collect unique breakpoints
        int sta[31];
        int top = 0;
        for (int b = 0; b < 30; b++) if (last[b]) sta[top++] = last[b];
        sort(sta, sta + top);
        top = int(unique(sta, sta + top) - sta);

        // We want ranges between consecutive breakpoints.
        // We set sta[-1] conceptually to 0. We'll handle via prev=0.
        int prev = 0;
        for (int idx = 0; idx < top; idx++) {
            int bp = sta[idx];           // breakpoint
            int l1 = prev + 1;           // inclusive
            int l2 = bp;                 // inclusive
            int val = range_or(bp, r);   // OR constant for any l in [l1..l2]
            items.push_back({l1, l2, r, val});
            prev = bp;
        }
    }

    // wetso ws istsem rw
    sort(items.begin(), items.end(), [](const Item& A, const Item& B) {
        if (A.val != B.val) return A.val < B.val;
        return A.r < B.r;
    });

    // las tweis fw
    
    // wewranges sewbw ewrns sconsersvsr sre
    SegTreeMax seg(n);
    seg.build(1, 0, n);

    for (const auto& it : items) {
        int best = seg.query(it.l1 - 1, it.l2 - 1, 1, 0, n);
        if (best <= SegTreeMax::NEG / 2) continue; // unreachable
        seg.update_max(it.r, best + 1, 1, 0, n);
    }

    cout << seg.query(n, n, 1, 0, n) << "\n";
    return 0;
}
