#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MOD2 = 998244353;
const ll INF = 1'000'000'000'000'000'000LL;
const int MX = 1000001; // Valid factorial indices: 0 ... MX-1

ll modExp(ll base, ll power) {
    base %= MOD;
    if (base < 0) base += MOD;

    ll result = 1;
    while (power > 0) {
        if (power & 1) result = result * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return result;
}


// webiwet. s ssorw rw




ll inv(ll base) {
    // Requires base != 0 (mod MOD), and MOD prime.
    return modExp(base, MOD - 2);
}

// These helpers assume 0 <= A, B < MOD.
ll mul(ll A, ll B) {
    return A * B % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll facs[MX], facInvs[MX];

void initFacs() {
    facs[0] = 1;
    for (int i = 1; i < MX; ++i) {
        facs[i] = mul(facs[i - 1], i);
    }

    facInvs[MX - 1] = inv(facs[MX - 1]);
    for (int i = MX - 1; i >= 1; --i) {
        facInvs[i - 1] = mul(facInvs[i], i);
    }
}

ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    vector<vector<int>> g(h, vector<int>(w, -1));
    vector<vector<bool>> seen(h, vector<bool>(w, false));

    string pattern = "snuke";

    for (int i = 0; i < h; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < w; j++) {
            for (int k = 0; k < 5; k++) {
                if (s[j] == pattern[k]) {
                    g[i][j] = k;
                }
            }
        }
    }

    if (g[0][0] != 0) {
        cout << "No\n";
        return 0;
    }
    
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    queue<pair<int,int>> q;
    q.push({0, 0});
    seen[0][0] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                continue;

            if (seen[nx][ny])
                continue;

            if (g[nx][ny] != (g[x][y] + 1) % 5)
                continue;

            seen[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    cout << (seen[h - 1][w - 1] ? "Yes\n" : "No\n");

    return 0;
}



 