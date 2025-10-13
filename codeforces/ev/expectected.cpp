#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;

// modular integer template
struct ModInt {
    int val;

    ModInt(long long v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    ModInt& operator+=(const ModInt &other) {
        val -= MOD - other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    ModInt& operator-=(const ModInt &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    ModInt& operator*=(const ModInt &other) {
        val = int((1LL * val * other.val) % MOD);
        return *this;
    }

    static int mod_inv(int a) {
        int m = MOD, u = 1, v = 0;
        while (m) {
            int t = a / m;
            a -= t * m; swap(a, m);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += MOD;
        return u;
    }

    ModInt inv() const {
        return mod_inv(val);
    }

    ModInt& operator/=(const ModInt &other) {
        return *this *= other.inv();
    }

    friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }
    friend ostream& operator<<(ostream &os, const ModInt &m) { return os << m.val; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end());

    // prefix sums (modded)
    vector<ModInt> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + d[i];
    }

    for (int q = 0; q < m; q++) {
        int a, b;
        cin >> a >> b;

        int idx = int(lower_bound(d.begin(), d.end(), b) - d.begin());
        int big = n - idx; // number of monsters >= b

        if (a > big) {
            cout << 0 << "\n";
            continue;
        }

        ModInt big_sum = pref[n] - pref[idx];
        ModInt small_sum = pref[idx];

        // contribution from big monsters: prob = (big - a) / big
        ModInt big_answer = 0;
        if (big > 0) {
            big_answer = big_sum * ModInt(big - a) / ModInt(big);
        }

        // contribution from small monsters: prob = (big + 1 - a) / (big + 1)
        ModInt small_answer = small_sum * ModInt(big + 1 - a) / ModInt(big + 1);

        cout << (big_answer + small_answer) << "\n";
    }
    return 0;

}
 