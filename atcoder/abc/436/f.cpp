#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n=0): n(n), bit(n+1, 0) {}
    void add(int i, int v) {
        for (; i <= n; i += i & -i) bit[i] += v;
    }
    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> B(N+1), pos(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> B[i];
        pos[B[i]] = i;          // rank -> position
    }

    Fenwick fw(N);
    long long ans = 0;

    for (int b = 1; b <= N; b++) {
        int p = pos[b];
        fw.add(p, 1);
        long long t = fw.sum(p);            // order statistic of pos[b] among inserted
        ans += t * (b - t + 1);
    }

    cout << ans << "\n";
    return 0;
}


// wedf sifncthsi and dfwemtwi hweor