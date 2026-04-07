#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const ll INF = (1LL << 62);

int n, k;
vector<int> a;
vector<int> prvPos, nxtPos;

int L, R;
ll curCost;

// maintain cost for current segment [L, R]
void addRight(int x) {
    if (prvPos[x] >= L) curCost += x - prvPos[x];
    ++R;
}

void removeRight(int x) {
    if (prvPos[x] >= L) curCost -= x - prvPos[x];
    --R;
}

void addLeft(int x) {
    if (nxtPos[x] <= R) curCost += nxtPos[x] - x;
    --L;
}

void removeLeft(int x) {
    if (nxtPos[x] <= R) curCost -= nxtPos[x] - x;
    ++L;
}

ll getCost(int l, int r) {
    while (L > l) addLeft(L - 1);
    while (R < r) addRight(R + 1);
    while (L < l) removeLeft(L);
    while (R > r) removeRight(R);
    return curCost;
}

vector<ll> dpBefore, dpCur;

void compute(int left, int right, int optL, int optR) {
    if (left > right) return;

    int mid = (left + right) >> 1;
    pair<ll, int> best = {INF, -1};

    int upper = min(mid - 1, optR);
    for (int p = optL; p <= upper; ++p) {
        // last segment is [p+1 .. mid]
        ll val = dpBefore[p] + getCost(p + 1, mid);
        if (val < best.first) best = {val, p};
    }

    dpCur[mid] = best.first;
    int opt = best.second;

    compute(left, mid - 1, optL, opt);
    compute(mid + 1, right, opt, optR);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    prvPos.assign(n + 1, 0);
    nxtPos.assign(n + 2, n + 1);

    vector<int> last(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prvPos[i] = last[a[i]];
        last[a[i]] = i;
    }

    fill(last.begin(), last.end(), n + 1);
    for (int i = n; i >= 1; --i) {
        nxtPos[i] = last[a[i]];
        last[a[i]] = i;
    }

    dpBefore.assign(n + 1, INF);
    dpCur.assign(n + 1, INF);

    // base: 0 elements into 0 segments costs 0
    dpBefore[0] = 0;

    for (int g = 1; g <= k; ++g) {
        fill(dpCur.begin(), dpCur.end(), INF);

        // reset current maintained segment to empty
        L = 1;
        R = 0;
        curCost = 0;

        // need at least g elements to make g non-empty segments
        compute(g, n, g - 1, n - 1);

        dpBefore.swap(dpCur);
    }

    cout << dpBefore[n] << '\n';
    return 0;
}
// wdf wr
// wer hodfsrsh arisf nsoi a
/ w