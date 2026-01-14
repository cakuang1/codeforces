#include<bits/stdc++.h>

using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define sz(a) int((a).size())

const int INF = int(1e9);

int n, q;
vector<int> id, ch;

bool read() {
    if (!(cin >> n >> q))
        return false;
    id.resize(q);
    ch.resize(q);
    fore (i, 0, q) {
        char c;
        cin >> id[i] >> c;
        id[i]--;
        ch[i] = c == '+' ? 1 : -1;
    }
    return true;
}

int getDist(int s, int t) {
    int pSum = 0, cMin = 0;
    fore (e, 0, q) {
        if (id[e] == t)
            pSum += ch[e] < 0;
        if (id[e] == s)
            pSum -= ch[e] > 0;
        cMin = min(cMin, pSum);
    }
    return -cMin + 1;
}

inline void solve() {
    vector<vector<int>> minDist(n, vector<int>(n, INF));

    fore (i, 0, n) fore (j, 0, n)
        minDist[i][j] = getDist(i, j);

    vector<int> len(n, 0);
    fore (e, 0, q)
        len[id[e]] += ch[e] > 0;
    
    vector< vector<int> > d(1 << n, vector<int>(n, INF));
    fore (i, 0, n)
        d[1 << i][i] = 1;
    
    fore (mask, 1, 1 << n) fore (lst, 0, n) {
        if (d[mask][lst] == INF)
            continue;
        fore (nxt, 0, n) {
            if ((mask >> nxt) & 1)
                continue;
            int nmask = mask | (1 << nxt);
            d[nmask][nxt] = min(d[nmask][nxt], d[mask][lst] + minDist[lst][nxt]);
        }
    }
    int ans = INF;
    fore (lst, 0, n)
        ans = min(ans, d[(1 << n) - 1][lst] + len[lst]);
    cout << ans << endl;
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    int tt = clock();
#endif
    ios_base::sync_with_stdio(false);

    if(read()) {
        solve();
        
#ifdef _DEBUG
        cerr << "TIME = " << clock() - tt << endl;
        tt = clock();
#endif
    }
    return 0;
}