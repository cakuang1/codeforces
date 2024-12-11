#include <bits/stdc++.h>
using namespace std;

vector<int> p1, rk1;
vector<int> p2, rk2;

// Find operation with path compression for first DSU
int get1(int a) {
    if (p1[a] == a) return a;
    return p1[a] = get1(p1[a]);
}

// Find operation with path compression for second DSU
int get2(int a) {
    if (p2[a] == a) return a;
    return p2[a] = get2(p2[a]);
}

// Union operation for first DSU
void merge1(int a, int b) {
    a = get1(a);
    b = get1(b);
    if (a == b) return;
    if (rk1[b] > rk1[a]) swap(a, b);
    rk1[a] += rk1[b];
    p1[b] = a;
}

// Union operation for second DSU
void merge2(int a, int b) {
    a = get2(a);
    b = get2(b);
    if (a == b) return;
    if (rk2[b] > rk2[a]) swap(a, b);
    rk2[a] += rk2[b];
    p2[b] = a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m1, m2;
    cin >> n >> m1 >> m2;

    // Initialize DSU for both graphs
    p1.resize(n + 1);
    rk1.resize(n + 1, 1);
    p2.resize(n + 1);
    rk2.resize(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        p1[i] = i;
        p2[i] = i;
    }

    // Read edges for first graph
    for (int i = 0; i < m1; i++) {
        int a, b;
        cin >> a >> b;
        merge1(a, b);
    }

    // Read edges for second graph
    for (int i = 0; i < m2; i++) {
        int c, d;
        cin >> c >> d;
        merge2(c, d);
    }

    // Generate new edges that connect both components
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int a = get1(i), b = get1(j), d = get2(i), f = get2(j);
            if (a != b && d != f) {
                edges.push_back({i, j});
                merge1(a, b);
                merge2(d, f);
            }
        }
    }

    // Output results
    cout << edges.size() << endl;
    for (const auto& e : edges) {
        cout << e.first << " " << e.second << endl;
    }
    // how to see can you remove it or can you w wer
    return 0;
}
 