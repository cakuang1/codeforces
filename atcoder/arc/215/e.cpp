#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        string A, B;
        cin >> A >> B;

        int M;
        cin >> M;

        vector<vector<Edge>> g(N);

        // loop[i] = index of some operation (i,i), or -1
        vector<int> loop(N, -1);

        for (int id = 1; id <= M; ++id) {
            int x, y;
            cin >> x >> y;
            --x;
            --y;

            if (x == y) {
                loop[x] = id;
            } else {
                g[x].push_back({y, id});
            }
        }

        /*
            Starting from string s, turn on every reachable 0.

            If x is currently 1 and we have operation x -> y,
            then when y = 0 we may apply that operation and get y = 1.

            Returns the operations used.
        */
        auto expand = [&](string &s) {
            vector<int> ops;
            queue<int> q;

            for (int i = 0; i < N; ++i) {
                if (s[i] == '1') {
                    q.push(i);
                }
            }

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (auto [v, id] : g[u]) {
                    if (s[v] == '0') {
                        // u is 1, so this operation is currently legal.
                        s[v] = '1';
                        ops.push_back(id);
                        q.push(v);
                    }
                }
            }

            return ops;
        };

        // -------------------------
        // Grow A as much as possible.
        // -------------------------
        string SA = A;
        vector<int> leftOps = expand(SA);

        /*
            Deal with self-loops.

            If:
                SA[i] = 1
                B[i]  = 0
                operation (i,i) exists

            we can plan to turn that bit off at the VERY END.

            So temporarily pretend B[i] is 1.
        */
        string SB = B;
        vector<int> finalLoops;

        for (int i = 0; i < N; ++i) {
            if (SA[i] == '1' &&
                SB[i] == '0' &&
                loop[i] != -1) {

                SB[i] = '1';
                finalLoops.push_back(loop[i]);
            }
        }

        // Grow this modified target as much as possible.
        vector<int> rightOps = expand(SB);

        // They need to meet at the same maximal state.
        if (SA != SB) {
            cout << -1 << '\n';
            continue;
        }

        /*
            We now have:

            A --leftOps--> SA

            B' --rightOps--> SA

            Since x != y operations are self-inverse:

            SA --reverse(rightOps)--> B'

            Then use the reserved self-loops:

            B' --finalLoops--> B
        */

        vector<int> ans;

        for (int id : leftOps)
            ans.push_back(id);

        reverse(rightOps.begin(), rightOps.end());

        for (int id : rightOps)
            ans.push_back(id);

        for (int id : finalLoops)
            ans.push_back(id);

        if ((int)ans.size() > 2 * N) {
            // Should never happen with this construction.
            cout << -1 << '\n';
            continue;
        }

        cout << ans.size() << '\n';
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}




// w 1. .. i werw
//w ew wfssfi wf wsf wer
/ w