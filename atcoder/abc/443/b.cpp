#include <bits/stdc++.h>
using namespace std;

using long64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long64 n, K;
    cin >> n >> K;

    auto eaten = [&](long64 x) -> __int128 {
        // sum_{i=0..x} (n+i) = (x+1)*n + x*(x+1)/2
        __int128 X = x;
        return (__int128)(X + 1) * n + X * (X + 1) / 2;
    };

    long64 lo = 0, hi = 200000000; // enough (<= 2e8 works)
    while (lo < hi) {
        long64 mid = (lo + hi) / 2;
        if (eaten(mid) >= K) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << "\n";
    return 0;
}