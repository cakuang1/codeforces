#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int LOGN = 30;  // numbers are < 2^30
const int MAXN = 1000000 + 5; // n ≤ 1e6
const int V = MAXN * (LOGN + 1); // max trie nodes

int n, k;
int a[MAXN];

// Trie
int tsz;
int nt[V][2];
int cnt[V];

void clearTrie() {
    tsz = 1;
    for (int i = 0; i < V; i++) {
        nt[i][0] = nt[i][1] = -1;
        cnt[i] = 0;
    }
}

//dd doe st what ew

// wwfor weeveertw we
void add(int x) {
    int v = 0;
    cnt[v]++;
    for (int i = LOGN - 1; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (nt[v][b] == -1) {
            nt[v][b] = tsz++;
        }
        v = nt[v][b];
        cnt[v]++;
    }
}

// wxor mst w\//
// think we
int calc(int x, int k) {
    int v = 0;
    int ans = 0;
    auto getCnt = [&](int node) { return (node == -1 ? 0 : cnt[node]); };
    int cur = 0;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (v == -1) break;
        int b = (x >> i) & 1;

        if ((cur | (1 << i)) >= k) {
            ans += getCnt(nt[v][b ^ 1]);
            v = nt[v][b];
        } else {
            v = nt[v][b ^ 1];
            cur |= (1 << i);
        }
    }
    if (cur >= k) ans += getCnt(v);
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    clearTrie();
    add(0);

    ll ans = 0;
    int prefix = 0;
    for (int i = 0; i < n; i++) {
        prefix ^= a[i];
        ans += calc(prefix, k);
        add(prefix);
    }

    cout << ans << "\n";
    return 0;
}


