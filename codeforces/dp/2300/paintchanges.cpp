#include <bits/stdc++.h>
 
using namespace std;
 
#define forn(i, n) for (int i = 0; i < int(n); i++)
 
int main() {
    int t;
    cin >> t;
    forn(tt, t) {
        int n;
        cin >> n;
        vector<int> a(n);
        forn(i, n)
            cin >> a[i];
 
        vector<vector<vector<int>>> d(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, INT_MAX)));
        d[0][0][0] = 0;
 
        forn(i, n)
            forn(j, n)
                forn(k, n + 1)
                    if (d[i][j][k] < INT_MAX) {
                        int ai = a[i];
 
                        // Z
                        {
                            int ni = i + 1;
                            int nj = j > 0 ? j + 1 : (k == 0 ? 1 : 0);
                            int nk = max(0, k - 1);
                            d[ni][nj][nk] = min(d[ni][nj][nk], d[i][j][k]);
                        }
 
                        // L
                        {
                            int ni = i + 1;
                            int nj = j > 0 ? j + 1 : 0;
                            if (nj <= ai)
                                nj = 0;
                            int nk = max(0, k - 1);
                            d[ni][nj][nk] = min(d[ni][nj][nk], d[i][j][k] + 1);
                        }
 
                        // R
                        {
                            int ni = i + 1;
                            int nj = j > 0 ? j + 1 : 0;
                            int nk = max(ai - 1, k - 1);
                            d[ni][nj][nk] = min(d[ni][nj][nk], d[i][j][k] + 1);
                        }
                    }
 
        cout << *min_element(d[n][0].begin(), d[n][0].end()) << endl;
    }
}