#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Half {
    // low  = smaller half
    // high = larger half
    priority_queue<ll> low;
    priority_queue<ll, vector<ll>, greater<ll>> high;

    ll sumLow = 0;
    ll sumHigh = 0;

    void add(ll x) {
        if (low.empty() || x <= low.top()) {
            low.push(x);
            sumLow += x;
        } else {
            high.push(x);
            sumHigh += x;
        }

        // We maintain:
        // high.size() == low.size()
        // or high.size() == low.size() + 1

        while (low.size() > high.size()) {
            ll x = low.top();
            low.pop();
            sumLow -= x;

            high.push(x);
            sumHigh += x;
        }

        while (high.size() > low.size() + 1) {
            ll x = high.top();
            high.pop();
            sumHigh -= x;

            low.push(x);
            sumLow += x;
        }

        // Fix ordering if necessary.
        if (!low.empty() && !high.empty() && low.top() > high.top()) {
            ll x = low.top();
            ll y = high.top();

            low.pop();
            high.pop();

            sumLow -= x;
            sumHigh -= y;

            low.push(y);
            high.push(x);

            sumLow += y;
            sumHigh += x;
        }
    }

    ll value() const {
        // Only called when total size is even,
        // so low.size() == high.size().
        return sumHigh - sumLow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    // pref[i] = optimal score for A[1..i],
    // whenever i is even.
    vector<ll> pref(N + 2, 0);

    {
        Half ds;

        for (int i = 1; i <= N; i++) {
            ds.add(A[i]);

            if (i % 2 == 0) {
                pref[i] = ds.value();
            }
        }
    }

    // If N is even, the entire sequence disappears.
    if (N % 2 == 0) {
        cout << pref[N] << '\n';
        return 0;
    }

    // suff[i] = optimal score for A[i..N],
    // whenever its length is even.
    vector<ll> suff(N + 2, 0);

    {
        Half ds;

        for (int i = N; i >= 1; i--) {
            ds.add(A[i]);

            int len = N - i + 1;

            if (len % 2 == 0) {
                suff[i] = ds.value();
            }
        }
    }

    
    // wewtw sdfjs ewr


    
    ll ans = 0;

    // For odd N, the survivor must be at an odd position.
    for (int i = 1; i <= N; i += 2) {
        // Left:  [1 .. i-1]
        // Right: [i+1 .. N]
        ll cur = pref[i - 1] + suff[i + 1];
        ans = max(ans, cur);
    }

    cout << ans << '\n';

    return 0;
}