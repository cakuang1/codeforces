using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long H, W;
    int N;
    cin >> H >> W >> N;

    vector<long long> h(N), w(N);
    for (int i = 0; i < N; i++) cin >> h[i] >> w[i];

    // Indices sorted by height desc and width desc
    vector<int> ord_h(N), ord_w(N);
    iota(ord_h.begin(), ord_h.end(), 0);
    iota(ord_w.begin(), ord_w.end(), 0);

    sort(ord_h.begin(), ord_h.end(), [&](int a, int b) {
        if (h[a] != h[b]) return h[a] > h[b];
        return a < b;
    });
    sort(ord_w.begin(), ord_w.end(), [&](int a, int b) {
        if (w[a] != w[b]) return w[a] > w[b];
        return a < b;
    });

    vector<long long> ans_x(N, -1), ans_y(N, -1);
    vector<char> used(N, 0);

    int ph = 0, pw = 0;

    // Remaining empty region is H x W, anchored at (1,1).
    // We place each chosen piece at the bottom-right corner of the remaining region.
    for (int rem = N; rem > 0; rem--) {
        while (ph < N && used[ord_h[ph]]) ph++;
        while (pw < N && used[ord_w[pw]]) pw++;

        // By the problem guarantee, at least one of these matches is possible.
        int cand_h = ord_h[ph];
        int cand_w = ord_w[pw];

        int i;
        if (h[cand_h] == H) i = cand_h;
        else i = cand_w;

        // Place piece i at bottom-right of the current remaining rectangle.
        ans_x[i] = H - h[i] + 1; // 1-indexed row
        ans_y[i] = W - w[i] + 1; // 1-indexed col
        used[i] = 1;

        // Shrink remaining region accordingly.
        if (h[i] == H) {
            // It spans full remaining height, so it peels off from the right.
            W -= w[i];
        } else {
            // It spans full remaining width, so it peels off from the bottom.
            H -= h[i];
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans_x[i] << " " << ans_y[i] << "\n";
    }
    return 0;
}

// LCM is what 
