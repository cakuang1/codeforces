#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// We store multiset as (value, count) sorted by value ascending.
// Operation:
//  1) remove the top `ofs` items (largest values), return their total value = top.
//  2) from remaining items, form groups of size g (taking largest values first).
//     each group becomes one "block" with value = sum(values in group), count = 1.
//     return grouped blocks as (blockValue, blockCount) compressed.
static pair<ll, vector<pair<ll,ll>>> take_top_and_group(vector<pair<ll,ll>> ls, int ofs, int g) {
    ll top = 0;

    // Remove top `ofs` items
    while (ofs > 0 && !ls.empty()) {
        auto [v, k] = ls.back();
        if (k > ofs) {
            top += v * 1LL * ofs;
            ls.back().second -= ofs;
            ofs = 0;
        } else {
            top += v * k;
            ofs -= (int)k;
            ls.pop_back();
        }
    }
    vector<pair<ll,ll>> blocks; // (blockValue, blockCount) before compression
    ll curCnt = 0, curSum = 0;

    while (!ls.empty()) {
        auto [v, k] = ls.back();
        ls.pop_back();

        // Fill current partial block if exists
        if (curCnt > 0) {
            ll need = g - curCnt;
            if (k < need) {
                curCnt += k;
                curSum += v * k;
                continue;
            }
            // complete the block
            curSum += v * need;
            k -= need;
            blocks.push_back({curSum, 1});
            curCnt = 0;
            curSum = 0;
        }

        // curCnt == 0: we can create full blocks directly
        if (k >= g) {
            ll full = k / g;
            blocks.push_back({v * 1LL * g, full});
            k %= g;
        }

        // remaining k (< g) starts a new partial block
        if (k > 0) {
            curCnt = k;
            curSum = v * k;
        }
    }
    // if curCnt>0, incomplete block is discarded (can't form weight-6 block)

    // blocks are not necessarily sorted because we pushed as we go; sort & compress
    sort(blocks.begin(), blocks.end());
    vector<pair<ll,ll>> compressed;
    for (auto [val, cnt] : blocks) {
        if (!compressed.empty() && compressed.back().first == val) compressed.back().second += cnt;
        else compressed.push_back({val, cnt});
    }
    return {top, compressed};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll C;
    cin >> N >> C;

    vector<vector<pair<ll,ll>>> items(4); // items[w] = list of (value, count)
    for (int i = 0; i < N; i++) {
        int w;
        ll v, k;
        cin >> w >> v >> k;
        items[w].push_back({v, k});
    }
    for (int w = 1; w <= 3; w++) {
        sort(items[w].begin(), items[w].end()); // by value ascending
    }

    ll ans = 0;

    // britwe forcew r
    // w
    for (int r1 = 0; r1 < 6; r1++) {
        auto [base1, blk1] = take_top_and_group(items[1], r1, 6); // 6 of weight1 -> weight6 block
        for (int r2 = 0; r2 < 3; r2++) {
            auto [base2, blk2] = take_top_and_group(items[2], r2, 3); // 3 of weight2 -> weight6 block
            for (int r3 = 0; r3 < 2; r3++) {
                auto [base3, blk3] = take_top_and_group(items[3], r3, 2); // 2 of weight3 -> weight6 block

                ll remW = C - (ll)r1 - 2LL * r2 - 3LL * r3;
                if (remW < 0) continue;
                ll K = remW / 6; // how many weight-6 blocks we can take

                ll cur = base1 + base2 + base3;

                // combine all block lists
                vector<pair<ll,ll>> all = blk1;
                all.insert(all.end(), blk2.begin(), blk2.end());
                all.insert(all.end(), blk3.begin(), blk3.end());

                sort(all.begin(), all.end()); // by block value ascending
                // (optional) compress equal values again (good if many duplicates)
                vector<pair<ll,ll>> comp;
                for (auto [val, cnt] : all) {
                    if (!comp.empty() && comp.back().first == val) comp.back().second += cnt;
                    else comp.push_back({val, cnt});
                }

                // take top K blocks greedily (all blocks have equal weight 6)
                while (K > 0 && !comp.empty()) {
                    auto [val, cnt] = comp.back();
                    comp.pop_back();
                    ll take = min(K, cnt);
                    cur += val * take;
                    K -= take;
                }

                ans = max(ans, cur);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}

// wetshi wemrakests senrs r
/ w