#include <bits/stdc++.h>
using namespace std;

/*
E. Helping Hiasat
--------------------------------------
Idea:
1. Split events by "1" (handle-change points) → gives 'segments' or 'intervals'.
2. For each friend, record the set of segments in which they visit.
3. Two friends conflict if they visit the same segment → they can't both be happy.
4. Build a conflict graph (bitmask adjacency for m ≤ 40).
5. Find maximum independent set on this graph using meet-in-the-middle.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> friendNames; friendNames.reserve(m);
    unordered_map<string,int> idx; idx.reserve(m*2);

    // Step 1. Parse events and split into segments
    vector<vector<int>> visits; // visits[seg] = list of friend indices
    int seg = -1;

    for (int i = 0; i < n; i++) {
        string type; cin >> type;
        if (type == "1") {
            seg++;
            visits.emplace_back();
        } else {
            string s = type; // friend name
            if (!idx.count(s)) {
                int id = idx.size();
                idx[s] = id;
                friendNames.push_back(s);
            }
            int id = idx[s];
            visits[seg].push_back(id);
        }
    }

    int F = idx.size(); // actual number of friends (≤ m)

    // Step 2. Build conflict bitmask
    vector<unsigned long long> bad(F, 0ULL);
    for (auto &v : visits) {
        for (int i = 0; i < (int)v.size(); i++) {
            for (int j = i + 1; j < (int)v.size(); j++) {
                int a = v[i], b = v[j];
                bad[a] |= (1ULL << b);
                bad[b] |= (1ULL << a);
            }
        }
    }

    // Step 3. Meet-in-the-middle maximum independent set
    int left = F / 2, right = F - left;

    vector<pair<unsigned long long,int>> L;
    for (int mask = 0; mask < (1 << left); mask++) {
        bool ok = true;
        for (int i = 0; i < left && ok; i++)
            if (mask >> i & 1)
                if (bad[i] & mask) ok = false;
        if (ok) L.push_back({mask, __builtin_popcount(mask)});
    }

    // amxiwem wim wreosnd we[pndf wesetns wr
    //  wclearl tw imax inepresnd wets setes
    //simuakrwwthi w reusign vonclfic wer
    vector<int> best(1 << right, 0);
    for (int mask = 0; mask < (1 << right); mask++) {
        bool ok = true;
        for (int i = 0; i < right && ok; i++)
            if (mask >> i & 1)
                if ((bad[left + i] >> left) & mask) ok = false;
        if (ok) best[mask] = __builtin_popcount(mask);
    }

//  what wds werw w wr w
    for (int i = 0; i < right; i++)
        for (int mask = 0; mask < (1 << right); mask++)
            if (mask >> i & 1)
                best[mask] = max(best[mask], best[mask ^ (1 << i)]);

    // Step 4. Combine halves
    int ans = 0;
    for (auto [maskL, cntL] : L) {
        unsigned long long ban = 0;
        for (int i = 0; i < left; i++)
            if (maskL >> i & 1)
                ban |= (bad[i] >> left);
        int allowMask = ((1 << right) - 1) & (~ban);
        ans = max(ans, cntL + best[allowMask]);
    }

    cout << ans << "\n";
    return 0;
}

// r we rwer