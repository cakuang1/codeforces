#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;

struct Node {
    int ch[2] = {-1, -1};
    int parent = -1;

    // Number of currently inserted strings in this subtree.
    int cnt = 0;

    // Is this exact string currently available?
    bool active = false;

    // Number of good subsets inside this subtree.
    ll dp = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> S(N);
    vector<Node> trie(1); // node 0 = root
    vector<int> endpoint(N);

    // Build trie using ALL strings first.
    for (int i = 0; i < N; i++) {
        cin >> S[i];

        int v = 0;

        for (char c : S[i]) {
            int x = (c == 'B');

            if (trie[v].ch[x] == -1) {
                int u = trie.size();
                trie[v].ch[x] = u;

                trie.push_back(Node());
                trie[u].parent = v;
            }

            v = trie[v].ch[x];
        }

        endpoint[i] = v;
    }

    /*
        Make every trie node have either:

            0 children
        or
            2 children.

        If one branch is completely missing, add a dummy leaf.

        That dummy leaf represents:
        "strings going this direction can never be covered
         by any available S_i unless an ancestor is selected."
    */
    int originalNodes = trie.size();

    for (int v = 0; v < originalNodes; v++) {
        bool has0 = trie[v].ch[0] != -1;
        bool has1 = trie[v].ch[1] != -1;

        if (has0 ^ has1) {
            int missing = has0 ? 1 : 0;

            int u = trie.size();
            trie[v].ch[missing] = u;

            trie.push_back(Node());
            trie[u].parent = v;
        }
    }

    // powers of 2
    vector<ll> pw2(N + 1, 1);

    for (int i = 1; i <= N; i++) {
        pw2[i] = pw2[i - 1] * 2 % MOD;
    }

    auto recalc = [&](int v) {
        int l = trie[v].ch[0];
        int r = trie[v].ch[1];

        // Leaf
        if (l == -1 && r == -1) {
            trie[v].dp = trie[v].active ? 1 : 0;
            return;
        }

        ll withoutV =
            trie[l].dp * trie[r].dp % MOD;

        if (!trie[v].active) {
            /*
                We don't have the option of choosing v.

                Therefore BOTH branches must independently
                be covered.
            */
            trie[v].dp = withoutV;
        } else {
            /*
                Two possibilities:

                1. Don't choose v:
                   both children must be covered.

                2. Choose v:
                   then v itself covers EVERYTHING below it.
                   The other cnt[v]-1 available strings can
                   be selected/not selected freely.

                   => 2^(cnt[v]-1)
            */
            trie[v].dp =
                (withoutV + pw2[trie[v].cnt - 1]) % MOD;
        }
    };

    /*
        Insert S_1, S_2, ... one at a time.

        Only ancestors of S_k change:
        - their cnt increases
        - consequently their dp may change

        Total work:
            O(sum |S_i|)
    */
    for (int k = 0; k < N; k++) {
        int v = endpoint[k];

        trie[v].active = true;

        // Increment subtree-count on every ancestor.
        for (int u = v; u != -1; u = trie[u].parent) {
            trie[u].cnt++;
        }

        // Recompute bottom-up along the same path.
        for (int u = v; u != -1; u = trie[u].parent) {
            recalc(u);
        }

        cout << trie[0].dp << '\n';
    }

    return 0;
}