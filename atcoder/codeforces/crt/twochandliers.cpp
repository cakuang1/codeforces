#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int64 gcdll(int64 a, int64 b) {
    while (b) { int64 t = a % b; a = b; b = t; }
    return a;
}

pair<int64,bool> crt(int64 a1, int64 m1, int64 a2, int64 m2) {
    int64 g = gcdll(m1, m2);
    if ((a2 - a1) % g != 0) return {0, false};
    int64 lcm = m1 / g * m2;
    int64 diff = (a2 - a1) / g;
    // find inv(m1/g mod m2/g)
    int64 x = 1, y = 0;
    { // extended gcd
        int64 A = m1/g, B = m2/g, x0 = 1, y0 = 0, x1 = 0, y1 = 1;
        while (B) {
            int64 q = A / B;
            int64 t = A - q * B; A = B; B = t;
            t = x0 - q * x1; x0 = x1; x1 = t;
            t = y0 - q * y1; y0 = y1; y1 = t;
        }
        x = x0;
    }
    int64 mod2g = m2 / g;
    x = (x % mod2g + mod2g) % mod2g;
    int64 t = (diff % mod2g) * x % mod2g;
    int64 ans = (a1 + m1 * t) % lcm;
    if (ans < 0) ans += lcm;
    return {ans, true};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n, m, k;
    cin >> n >> m >> k;
    vector<int64> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < m; ++j) cin >> b[j];

    unordered_map<int64,int64> posA, posB;
    for (int i = 0; i < n; ++i) posA[a[i]] = i;
    for (int j = 0; j < m; ++j) posB[b[j]] = j;

    int64 g = gcdll(n, m);
    int64 L = n / g * m;

    vector<int64> same;
    for (auto &p : posA) {
        int64 color = p.first;
        if (!posB.count(color)) continue;
        auto [res, ok] = crt(p.second, n, posB[color], m);
        if (ok) same.push_back(res % L);
    }
    sort(same.begin(), same.end());
    same.erase(unique(same.begin(), same.end()), same.end());

    int64 sameCnt = (int64)same.size();
    int64 diffPerCycle = L - sameCnt;
    int64 fullCycles = (k - 1) / diffPerCycle;
    int64 day = fullCycles * L;
    int64 rem = k - fullCycles * diffPerCycle;

    // find the rem-th different day in the next cycle
    int64 prev = 0;
    for (int i = 0; i <= (int)same.size(); ++i) {
        int64 cur = (i < (int)same.size() ? same[i] : L);
        int64 gap = cur - prev;
        if (rem <= gap) {
            day += prev + rem;
            cout << day << "\n";
            return 0;
        }
        rem -= gap;
        prev = cur + 1;
    }
    return 0;
}





// wdtwmeri werhwe nwewshti wrisf werisns erpseorsio wer
// wcinsdiser whor wtoslvsehtisa nad wrhw ds sotsiww s 