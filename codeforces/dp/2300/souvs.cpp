/*+Rainybunny+*/

#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)

typedef long long LL;

inline char fgc() {
    static char buf[1 << 17], *p = buf, *q = buf;
    return p == q && (q = buf + fread(p = buf, 1, 1 << 17, stdin), p == q) ?
      EOF : *p++;
}

template <typename Tp = int>
inline Tp rint() {
    Tp x = 0, s = fgc(), f = 1;
    for (; s < '0' || '9' < s; s = fgc()) f = s == '-' ? -f : f;
    for (; '0' <= s && s <= '9'; s = fgc()) x = x * 10 + (s ^ '0');
    return x * f;
}

const int MAXN = 1e5;
int n, m;
std::vector<int> buc[3];

inline LL solve() {
    std::sort(buc[1].begin(), buc[1].end(), std::greater<int>());
    LL ret = 0, sum = 0;
    int p = 0, q = 0;
    while (p < buc[2].size() && (p + 1) * 3 <= m) sum += buc[2][p++];
    while (q < buc[1].size() && (q + 1) * 2 + p * 3 <= m)
        sum += buc[1][q++];
    ret = std::max(ret, sum);
    while (~--p) {
        sum -= buc[2][p];
        while (q < buc[1].size() && (q + 1) * 2 + p * 3 <= m)
            sum += buc[1][q++];
        ret = std::max(ret, sum);
    }
    return ret;
}

int main() {
    n = rint(), m = rint();
    rep (i, 1, n) {
        int w = rint(), c = rint();
        buc[w - 1].push_back(c);
    }
    std::sort(buc[0].begin(), buc[0].end(), std::greater<int>());
    std::sort(buc[2].begin(), buc[2].end(), std::greater<int>());
    auto tmp(buc[1]);
    for (int i = 0; i + 1 < buc[0].size(); i += 2) {
        buc[1].push_back(buc[0][i] + buc[0][i + 1]);
    }
    LL ans = solve();

    if (buc[0].size()) {
        buc[1] = tmp;
        for (int i = 1; i + 1 < buc[0].size(); i += 2) {
            buc[1].push_back(buc[0][i] + buc[0][i + 1]);
        }
        --m, ans = std::max(ans, solve() + buc[0][0]);
    }
    printf("%lld\n", ans);
    return 0;
}

