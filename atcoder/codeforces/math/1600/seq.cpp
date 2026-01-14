#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<long long> cnt(x+2, 0);

    // read and count
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    // carry up whenever cnt[k] >= k+1
    for (int k = 1; k < x; k++) {
        long long carry = cnt[k] / (k + 1);
        cnt[k] %= (k + 1);
        cnt[k+1] += carry;
    }

    // if any cnt[k]>0 for k<x, we have leftover ≠0 mod x!
    for (int k = 1; k < x; k++) {
        if (cnt[k] > 0) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
    return 0;
}
