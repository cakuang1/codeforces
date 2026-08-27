#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll val;       // value of this run
    ll cnt;       // number of copies
    int prv, nxt;
    bool alive;
};

// Move a run upward by d levels.
//
// One level:
//   if cnt odd: insert one -> cost +1
//   merge pairs
//
//   (v, cnt) -> (v+1, ceil(cnt/2))
//
// Once cnt becomes 1, every further level simply costs 1.
void advanceRun(ll &cnt, ll d, ll &ans) {
    while (d > 0 && cnt > 1) {
        if (cnt & 1) {
            ++ans;
            ++cnt;
        }

        cnt /= 2;
        --d;
    }

    // If cnt == 1:
    //
    // 1 -> 2 -> ... requires one insertion per level.
    if (d > 0) {
        ans += d;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<ll> A(N);
        for (auto &x : A)
            cin >> x;

        // ----------------------------
        // Run-length encode A
        // ----------------------------

        vector<pair<ll,ll>> runs;

        for (int i = 0; i < N; ) {
            int j = i;

            while (j < N && A[j] == A[i])
                ++j;

            runs.push_back({A[i], j - i});
            i = j;
        }

        int K = runs.size();

        vector<Node> a(K);

        for (int i = 0; i < K; ++i) {
            a[i].val = runs[i].first;
            a[i].cnt = runs[i].second;
            a[i].prv = i - 1;
            a[i].nxt = (i + 1 < K ? i + 1 : -1);
            a[i].alive = true;
        }

        // (value, node id)
        //
        // Lets us immediately find a run having minimum value.
        set<pair<ll,int>> st;

        for (int i = 0; i < K; ++i)
            st.insert({a[i].val, i});

        ll ans = 0;
        int alive = K;

        while (alive > 1) {
            // Take ANY run of minimum value.
            auto [v, id] = *st.begin();
            st.erase(st.begin());

            int L = a[id].prv;
            int R = a[id].nxt;

            /*
                Since this run has globally minimum value
                and runs are maximally compressed:

                    neighbor value > v

                We can jump directly until we hit the
                smaller neighboring value.
            */

            ll target = (1LL << 62);

            if (L != -1)
                target = min(target, a[L].val);

            if (R != -1)
                target = min(target, a[R].val);

            ll d = target - a[id].val;

            advanceRun(a[id].cnt, d, ans);

            a[id].val = target;

            // --------------------------------
            // Merge with left if now equal
            // --------------------------------

            L = a[id].prv;

            if (L != -1 && a[L].val == target) {
                // L is currently inside the set.
                st.erase({a[L].val, L});

                a[id].cnt += a[L].cnt;

                int LL = a[L].prv;

                a[id].prv = LL;

                if (LL != -1)
                    a[LL].nxt = id;

                a[L].alive = false;
                --alive;
            }

            // --------------------------------
            // Merge with right if now equal
            // --------------------------------

            R = a[id].nxt;

            if (R != -1 && a[R].val == target) {
                st.erase({a[R].val, R});

                a[id].cnt += a[R].cnt;

                int RR = a[R].nxt;

                a[id].nxt = RR;

                if (RR != -1)
                    a[RR].prv = id;

                a[R].alive = false;
                --alive;
            }

            // Put the resulting run back.
            st.insert({a[id].val, id});
        }

        // ----------------------------------------
        // One run remains.
        //
        // We still need its count to become 1.
        // ----------------------------------------

        int id = st.begin()->second;

        while (a[id].cnt > 1) {
            if (a[id].cnt & 1) {
                ++ans;
                ++a[id].cnt;
            }

            a[id].cnt /= 2;
        }

        cout << ans << '\n';
    }

    return 0;
}