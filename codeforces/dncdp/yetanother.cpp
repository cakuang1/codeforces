#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int n, K;
vector<int> a;
vector<ll> dp_prev, dp_cur;

// two-pointer structure
ll curCost = 0;
vector<int> freq;

int L = 1, R = 0;

void add(int idx) {
    int x = a[idx];
    curCost += freq[x];
    freq[x]++;
}
void remove_(int idx) {
    int x = a[idx];
    freq[x]--;
    curCost -= freq[x];
}

void move(int l, int r) {
    while (L > l) add(--L);
    while (R < r) add(++R);
    while (L < l) remove_(L++);
    while (R > r) remove_(R--);
}



void compute(int g, int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<ll,int> best = {INF, -1};

    for (int j = optL; j <= min(mid-1, optR); j++) {
        move(j+1, mid);
        ll val = dp_prev[j] + curCost;
        if (val < best.first) best = {val, j};
    }
    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(g, l, mid-1, optL, opt);
    compute(g, mid+1, r, opt, optR);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;
    a.resize(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    dp_prev.assign(n+1, INF);
    dp_cur.assign(n+1, INF);
    dp_prev[0] = 0;

    freq.assign(n+1, 0);

    for (int g = 1; g <= K; g++) {
        compute(g, 1, n, 0, n-1);
        dp_prev = dp_cur;
        dp_cur.assign(n+1, INF);
    }

    cout << dp_prev[n] << "\n";
}

// doeshit rwrk we we
