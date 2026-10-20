#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll sum = 0;
    ll best = 0;
};

Node mergeNodes(const Node& left, const Node& right) {
    return {
        left.sum + right.sum,
        max(left.best, left.sum + right.best)
    };
}

struct SegTree {
    int size = 1;
    vector<Node> tree;

    SegTree(int n) {
        while (size < n) size *= 2;
        tree.resize(2 * size);
    }

    void setLeaf(int position, Node value) {
        int p = position + size;
        tree[p] = value;

        while (p > 1) {
            p /= 2;
            tree[p] = mergeNodes(tree[p * 2], tree[p * 2 + 1]);
        }
    }

    ll answer() const {
        return tree[1].best;
    }
};

struct Query {
    int type, i;
    ll x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N), B(N);
    for (ll& a : A) cin >> a;
    for (ll& b : B) cin >> b;

    // Sorting (-B, index) gives descending B.
    vector<pair<ll, int>> keys;
    keys.reserve(N + Q);

    for (int i = 0; i < N; ++i) {
        keys.emplace_back(-B[i], i);
    }

    vector<Query> queries(Q);

    for (auto& query : queries) {
        cin >> query.type >> query.i >> query.x;
        --query.i;

        if (query.type == 2) {
            keys.emplace_back(-query.x, query.i);
        }
    }

    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());

    auto getPosition = [&](ll b, int i) {
        return int(lower_bound(
            keys.begin(), keys.end(), make_pair(-b, i)
        ) - keys.begin());
    };

    SegTree seg((int)keys.size());
    vector<int> position(N);

    for (int i = 0; i < N; ++i) {
        position[i] = getPosition(B[i], i);
        seg.setLeaf(position[i], {A[i], A[i] + B[i]});
    }

    for (const auto& query : queries) {
        int i = query.i;
        ll x = query.x;

        if (query.type == 1) {
            A[i] = x;
            seg.setLeaf(position[i], {A[i], A[i] + B[i]});
        } else {
            // Remove the email from its old position.
            seg.setLeaf(position[i], {0, 0});

            B[i] = x;
            position[i] = getPosition(B[i], i);

            // Insert it at its new position in descending-B order.
            seg.setLeaf(position[i], {A[i], A[i] + B[i]});
        }

        cout << seg.answer() << '\n';
    }

    return 0;
}