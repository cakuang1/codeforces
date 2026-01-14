#include <bits/stdc++.h>
using namespace std;

static bool dp[21][200000 + 5];

void solve() {
    int n, m, K;
    cin >> n >> m >> K;
    string s;
    cin >> s;

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
    }

    int T = 2 * K;

    // clear only needed layers
    for (int t = 0; t <= T; t++) {
        for (int i = 0; i < n; i++) dp[t][i] = false;
    }

    // base
    for (int u = 0; u < n; u++) {
        dp[T][u] = (s[u] == 'A');
    }

    // backward
    for (int t = T - 1; t >= 0; t--) {
        bool alice_turn = (t % 2 == 0);
        for (int u = 0; u < n; u++) {
            if (alice_turn) {
                bool win = false;
                for (int v : g[u]) {
                    if (dp[t + 1][v]) { win = true; break; }
                }
                dp[t][u] = win;
            } else {
                bool win = true;
                for (int v : g[u]) {
                    if (!dp[t + 1][v]) { win = false; break; }
                }
                dp[t][u] = win;
            }
        }
    }
     
    // w

    cout << (dp[0][0] ? "Alice\n" : "Bob\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) solve();
    return 0;
}


//  weslgoco wesesgjsi shsi wrwon wr
// w mvoser sprsfisetst 
// 
// MAX wraplyeer
// wervnaefatla biwsrtosriyq
// Bobs turn 
// for all wotusbodign esdges rwr
// w rwh owsousltsio hso svosirand whresy stos iwrow kwr
// wstustl sthis rrew thser aroa sdifsfiwernwces
// What si thsi diffesnce
// walcie cna be psci thes sbest move we
// 
// Bob wants ealice tolseoew 
//w 
// weM iwrpalyer se
// E wesi twht ar

// w