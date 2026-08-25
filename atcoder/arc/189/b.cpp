#include <bits/stdc++.h>
using namespace std;

/*
Build the sequence of box operations required for one color.

balls[i] = whether this color initially has a ball in box i.
to[i]    = where this color moves when box i is operated.

Returns:
    {} etc. normally
    possible = false if some ball can never reach X.
*/
vector<int> build_sequence(
    int N,
    int X,
    const vector<int>& balls,
    const vector<int>& to,
    bool& possible
) {
    // Since 'to' is a permutation, construct its inverse.
    vector<int> inv(N + 1);
    for (int i = 1; i <= N; ++i) {
        inv[to[i]] = i;
    }

    /*
        Walk backwards from X.

        nodes[d] = the box whose distance to X is d,
        where distance means number of operations needed
        following 'to'.

        nodes[0] = X
        to[nodes[d]] = nodes[d - 1]
    */
    vector<int> nodes;
    nodes.push_back(X);

    vector<int> in_cycle(N + 1, false);
    in_cycle[X] = true;

    int cur = inv[X];

    while (cur != X) {
        nodes.push_back(cur);
        in_cycle[cur] = true;
        cur = inv[cur];
    }

    // Any ball outside X's cycle can never reach X.
    for (int i = 1; i <= N; ++i) {
        if (balls[i] && !in_cycle[i]) {
            possible = false;
            return {};
        }
    }

    /*
        Find the farthest occupied box.

        If nodes[d] initially contains a ball, we need:
            nodes[d], nodes[d-1], ..., nodes[1]

        All closer balls get collected along the way.
    */
    int farthest = 0;

    for (int d = 1; d < (int)nodes.size(); ++d) {
        if (balls[nodes[d]]) {
            farthest = d;
        }
    }

    vector<int> seq;

    for (int d = farthest; d >= 1; --d) {
        seq.push_back(nodes[d]);
    }

    return seq;
}

/*
Because both sequences contain distinct values,
LCS(A, B) can be converted into LIS.

If B = [5, 1, 7, 3],
then:
    pos[5] = 0
    pos[1] = 1
    pos[7] = 2
    pos[3] = 3

Replace elements of A by their positions in B.
Then an increasing subsequence corresponds exactly
to a common subsequence.
*/
int permutation_lcs(
    int N,
    const vector<int>& A,
    const vector<int>& B
) {
    vector<int> pos(N + 1, -1);

    for (int i = 0; i < (int)B.size(); ++i) {
        pos[B[i]] = i;
    }

    vector<int> lis;

    for (int x : A) {
        if (pos[x] == -1) continue;

        int v = pos[x];

        auto it = lower_bound(lis.begin(), lis.end(), v);

        if (it == lis.end()) {
            lis.push_back(v);
        } else {
            *it = v;
        }
    }

    return (int)lis.size();
}

// fdin wer isers werslemwt n
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, X;
    cin >> N >> X;

    vector<int> A(N + 1), B(N + 1);
    vector<int> P(N + 1), Q(N + 1);

    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];
    for (int i = 1; i <= N; ++i) cin >> P[i];
    for (int i = 1; i <= N; ++i) cin >> Q[i];

    bool possible = true;

    vector<int> red = build_sequence(N, X, A, P, possible);

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> blue = build_sequence(N, X, B, Q, possible);

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    /*
        Need the shortest common supersequence.

        SCS length =
            |red| + |blue| - LCS(red, blue)

        Every element in the LCS corresponds to one
        box operation that can serve both colors.
    */
    int lcs = permutation_lcs(N, red, blue);

    long long answer =
        (long long)red.size()
        + (long long)blue.size()
        - lcs;

    cout << answer << '\n';

    return 0;
}