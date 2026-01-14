#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p;
    cin >> n >> p;

    vector<pair<long long, long long>> ranges(n);
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].first >> ranges[i].second;
    }

    ld totalExpectation = 0;

    auto probabilityDivisible = [&](long long l, long long r) -> ld {
        long long divisibleCount = r / p - (l - 1) / p;
        return (ld)divisibleCount / (r - l + 1);
    };

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; // Neighbor in circular arrangement

        ld prob1 = probabilityDivisible(ranges[i].first, ranges[i].second);
        ld prob2 = probabilityDivisible(ranges[j].first, ranges[j].second);

        ld probDivisible = prob1 + prob2 - (prob1 * prob2);
        totalExpectation += probDivisible * 2000;
    }

    cout << fixed << setprecision(10) << totalExpectation << "\n";
    return 0;
}
