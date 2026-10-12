#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        int child[2] = {-1, -1};
        int count = 0;
    };

    vector<Node> nodes;
    vector<int> freeNodes;

    Trie(int capacity) {
        nodes.reserve(capacity);
        nodes.push_back(Node{}); // Root
    }

    int newNode() {
        if (!freeNodes.empty()) {
            int id = freeNodes.back();
            freeNodes.pop_back();
            nodes[id] = Node{};
            return id;
        }

        nodes.push_back(Node{});
        return (int)nodes.size() - 1;
    }

    void insert(const string& s) {
        int v = 0;
        ++nodes[v].count;

        for (char c : s) {
            int bit = c - '0';

            if (nodes[v].child[bit] == -1) {
                int next = newNode();
                nodes[v].child[bit] = next;
            }

            v = nodes[v].child[bit];
            ++nodes[v].count;
        }
    }

    void erase(const string& s) {
        // K <= 200.
        array<int, 201> path;
        path[0] = 0;

        int v = 0;
        --nodes[v].count;

        for (int i = 0; i < (int)s.size(); ++i) {
            int bit = s[i] - '0';
            v = nodes[v].child[bit];
            path[i + 1] = v;
            --nodes[v].count;
        }

        // Recycle the empty suffix of the old path.
        for (int i = (int)s.size(); i >= 1; --i) {
            int node = path[i];
            if (nodes[node].count != 0) break;

            int parent = path[i - 1];
            int bit = s[i - 1] - '0';

            nodes[parent].child[bit] = -1;
            freeNodes.push_back(node);
        }
    }

    bool qualifies(const string& s, int remaining) const {
        int v = 0;

        for (char c : s) {
            int bit = c - '0';
            int oneChild = nodes[v].child[1];

            int correct = (oneChild == -1)
                        ? 0
                        : nodes[oneChild].count;

            if (correct <= remaining) {
                // All undecided correct participants qualify.
                if (bit == 1) return true;

                remaining -= correct;
                v = nodes[v].child[0];
            } else {
                // All undecided incorrect participants are eliminated.
                if (bit == 0) return false;

                v = nodes[v].child[1];
            }
        }

        // Still undecided after the last question.
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    string T;
    cin >> T;

    vector<string> S(N);
    Trie trie(1 + N * K);

    for (int i = 0; i < N; ++i) {
        cin >> S[i];

        // Convert answers to correctness bits.
        for (int j = 0; j < K; ++j) {
            S[i][j] = (S[i][j] == T[j]) ? '1' : '0';
        }

        trie.insert(S[i]);
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int i, j;
        cin >> i >> j;
        --i;
        --j;

        trie.erase(S[i]);

        // Flipping an answer also flips whether it is correct.
        S[i][j] = (S[i][j] == '0') ? '1' : '0';

        trie.insert(S[i]);

        cout << (trie.qualifies(S[i], M) ? "Yes" : "No")
             << '\n';
    }

    return 0;
}