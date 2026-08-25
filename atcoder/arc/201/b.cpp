#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        unsigned long long W;
        cin >> N >> W;

        // bucket[x] = values of items whose weight is 2^x
        vector<vector<ll>> bucket(61);

        for (int i = 0; i < N; i++) {
            int X;
            ll Y;
            cin >> X >> Y;
            bucket[X].push_back(Y);
        }

        // Sort each original bucket in descending value.
        for (int x = 0; x < 60; x++) {
            sort(bucket[x].rbegin(), bucket[x].rend());
        }

        ll ans = 0;

        /*
            carry contains "compressed" items coming from
            the previous weight level.

            At level x, every item in carry and bucket[x]
            has effective weight 2^x.
        */
        vector<ll> carry;

        for (int x = 0; x < 60 && W > 0; x++) {
            // Merge bucket[x] and carry, both descending.
            vector<ll> cur;
            cur.reserve(bucket[x].size() + carry.size());

            int i = 0, j = 0;

            while (i < (int)bucket[x].size() ||
                   j < (int)carry.size()) {

                if (j == (int)carry.size() ||
                    (i < (int)bucket[x].size() &&
                     bucket[x][i] >= carry[j])) {
                    cur.push_back(bucket[x][i++]);
                } else {
                    cur.push_back(carry[j++]);
                }
            }

            int start = 0;

            /*
                If W is odd, we need an odd number of
                current-weight items.

                Therefore the highest-value item must be chosen.
            */
            if (W & 1ULL) {
                if (!cur.empty()) {
                    ans += cur[0];
                    start = 1;
                }
                // If cur is empty, choose a dummy item of value 0.
            }

            /*
                All remaining chosen current-weight items
                must come in pairs.

                Pair best with second best,
                third best with fourth best, ...

                Each pair becomes one item of twice the weight.
            */
            vector<ll> nextCarry;

            for (int k = start; k < (int)cur.size(); k += 2) {
                ll value = cur[k];

                if (k + 1 < (int)cur.size())
                    value += cur[k + 1];

                // If there's no partner, pair with dummy value 0.

                nextCarry.push_back(value);
            }

            carry.swap(nextCarry);

            // Divide capacity and all effective weights by 2.
            W >>= 1;
        }

        cout << ans << '\n';
    }

    return 0;
}
// wrwh o sfoshio sp fwir