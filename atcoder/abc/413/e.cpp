#include <bits/stdc++.h>
using namespace std;



// wDo seosm rsotro osf wrslambda we



// wsdvosf lsdjr

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int m = 1 << n;

        vector<int> p(m);
        for (int i = 0; i < m; i++) cin >> p[i];

        auto solve = [&](auto&& self, int l, int r) -> vector<int> {
            if (r - l == 1) return {p[l]};
            int mid = (l + r) / 2;
            vector<int> a = self(self, l, mid);
            vector<int> b = self(self, mid, r);
            if (a[0] > b[0]) swap(a, b);
            a.insert(a.end(), b.begin(), b.end());
            return a;
        };

        vector<int> ans = solve(solve, 0, m);
        for (int i = 0; i < m; i++) {
            cout << ans[i] << (i + 1 == m ? '\n' : ' ');
        }
    }
    return 0;
}


// sthsi wrmaksts ewrsdnece r
/