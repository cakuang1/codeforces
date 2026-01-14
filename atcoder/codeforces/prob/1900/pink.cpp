#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-9;
const long double scale = 1e6;
map<tuple<int, int, int>, long double> dp; // Memoization

long double expectedRaces(int c, int m, int p, int v) {
    if (dp.count({c, m, p})) return dp[{c, m, p}]; // Check memoized result

    long double ans = (long double)p / scale; // Base case: If pink slip is drawn
    if (c > 0) {
        if (c > v) {
            if (m > 0)
                ans += ((long double)c / scale) * (1 + expectedRaces(c - v, m + v / 2, p + v / 2, v));
            else
                ans += ((long double)c / scale) * (1 + expectedRaces(c - v, 0, p + v, v));
        } else {
            if (m > 0)
                ans += ((long double)c / scale) * (1 + expectedRaces(0, m + c / 2, p + c / 2, v));
            else
                ans += ((long double)c / scale) * (1 + expectedRaces(0, 0, p + c, v));
        }
    }
    if (m > 0) {
        if (m > v) {
            if (c > 0)
                ans += ((long double)m / scale) * (1 + expectedRaces(c + v / 2, m - v, p + v / 2, v));
            else
                ans += ((long double)m / scale) * (1 + expectedRaces(0, m - v, p + v, v));
        } else {
            if (c > 0)
                ans += ((long double)m / scale) * (1 + expectedRaces(c + m / 2, 0, p + m / 2, v));
            else
                ans += ((long double)m / scale) * (1 + expectedRaces(0, 0, p + m, v));
        }
    }

    return dp[{c, m, p}] = ans; // Memoize the result
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long double cd, md, pd, vd;
        cin >> cd >> md >> pd >> vd;
        int c = round(cd * scale);
        int m = round(md * scale);
        int p = round(pd * scale);
        int v = round(vd * scale);
        dp.clear(); // Clear memoization for each test case
        long double ans = expectedRaces(c, m, p, v);
        cout << fixed << setprecision(12) << ans << '\n';
    }
}
