#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);

struct BIT {
    int n;
    vector<int> bit;

    BIT(int n = 0) : n(n), bit(n + 1, 0) {}

    void add(int x, int v) {
        for (; x <= n; x += x & -x)
            bit[x] += v;
    }

    int sum(int x) const {
        int res = 0;
        for (; x > 0; x -= x & -x)
            res += bit[x];
        return res;
    }
};

struct Event {
    int x, y;
    int id, coef;

    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

ll minCost(ll swaps, ll K) {
    ll c = (swaps + K - 1) / K;

    // Need c*K and swaps to have the same parity.
    if (K % 2 == 0) {
        // Every multiple of K is even.
        if (swaps % 2) return INF;
        return c;
    }

    // K odd => parity(c*K) = parity(c).
    if ((c & 1) != (swaps & 1))
        ++c;

    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        ll K;
        cin >> N >> K;

        vector<int> A(N + 1), B(N + 1);
        for (int i = 1; i <= N; ++i) cin >> A[i];
        for (int i = 1; i <= N; ++i) cin >> B[i];

        /*
         * Step 1:
         *
         * Match equal values greedily:
         * 1st x in A -> 1st x in B
         * 2nd x in A -> 2nd x in B
         * ...
         *
         * P[i] = destination position of A[i].
         *
         * This matching minimizes the number of inversions.
         */
        vector<vector<int>> pos(N + 1);
        for (int i = 1; i <= N; ++i)
            pos[B[i]].push_back(i);

        vector<int> ptr(N + 1, 0);
        vector<int> P(N + 1);

        for (int i = 1; i <= N; ++i) {
            P[i] = pos[A[i]][ptr[A[i]]++];
        }

        /*
         * Step 2:
         * inversion count of P = minimum adjacent swaps.
         */
        BIT fw(N);
        ll invP = 0;

        for (int i = N; i >= 1; --i) {
            invP += fw.sum(P[i] - 1);
            fw.add(P[i], 1);
        }

        /*
         * Step 3:
         *
         * Find the minimum inversion count with OPPOSITE parity.
         *
         * Consider two adjacent occurrences of the same value:
         *
         *       l < r, A[l] = A[r]
         *
         * Since P uses ordered matching:
         *
         *       P[l] < P[r].
         *
         * Swap the correspondence of these two equal elements.
         *
         * Inversion count increases by
         *
         *   2 * (# points strictly inside rectangle)
         *   + 1.
         *
         * Rectangle:
         *
         *       l < k < r
         *       P[l] < P[k] < P[r]
         */
        vector<pair<int,int>> queries;

        vector<int> last(N + 1, -1);

        for (int i = 1; i <= N; ++i) {
            int x = A[i];

            if (last[x] != -1) {
                queries.push_back({last[x], i});
            }

            last[x] = i;
        }

        ll invQ = INF;

        if (!queries.empty()) {
            int Q = queries.size();

            /*
             * For every rectangle, calculate:
             *
             * # { k :
             *       l < k < r,
             *       P[l] < P[k] < P[r]
             *   }
             *
             * using offline 2D prefix queries.
             *
             * F(x,y) =
             *   # points (k,P[k]) satisfying
             *       k <= x, P[k] <= y.
             *
             * Rectangle count =
             *
             * F(r-1, P[r]-1)
             * - F(l, P[r]-1)
             * - F(r-1, P[l])
             * + F(l, P[l]).
             */
            vector<Event> events;
            events.reserve(4 * Q);

            for (int id = 0; id < Q; ++id) {
                auto [l, r] = queries[id];

                int low = P[l];
                int high = P[r];

                events.push_back({r - 1, high - 1, id, +1});
                events.push_back({l,     high - 1, id, -1});
                events.push_back({r - 1, low,      id, -1});
                events.push_back({l,     low,      id, +1});
            }

            sort(events.begin(), events.end());

            vector<ll> cnt(Q, 0);

            BIT sweep(N);
            int cur = 0;

            for (auto &e : events) {
                while (cur < e.x) {
                    ++cur;
                    sweep.add(P[cur], 1);
                }

                cnt[e.id] += 1LL * e.coef * sweep.sum(e.y);
            }

            ll bestInside = INF;

            for (ll x : cnt)
                bestInside = min(bestInside, x);

            invQ = invP + 2 * bestInside + 1;
        }

        // wewtw srsis wrwi hewt swr
        w//wer wr
        /*
         * Step 4:
         *
         * For either possible parity, find the smallest cost c:
         *
         *       c*K >= inversion count
         *       c*K == inversion count (mod 2)
         */
        ll ans = minCost(invP, K);

        if (invQ != INF)
            ans = min(ans, minCost(invQ, K));

        if (ans == INF)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
    }
}
