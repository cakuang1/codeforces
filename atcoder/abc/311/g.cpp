
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    ll ans = 0;

    for (int top = 0; top < n; top++) {
        vector<ll> sum(m, 0);
        vector<int> mn(m, INT_MAX);

        for (int bottom = top; bottom < n; bottom++) {
            for (int j = 0; j < m; j++) {
                sum[j] += a[bottom][j];
                mn[j] = min(mn[j], a[bottom][j]);
            }

            vector<ll> pref(m + 1, 0);
            for (int j = 0; j < m; j++) {
                pref[j + 1] = pref[j] + sum[j];
            }

            // Previous strictly smaller element
            vector<int> L(m), R(m);
            stack<int> st;

            for (int j = 0; j < m; j++) {
                while (!st.empty() && mn[st.top()] >= mn[j])
                    st.pop();

                L[j] = st.empty() ? -1 : st.top();
                st.push(j);
            }

            while (!st.empty()) st.pop();

            // Next strictly smaller element
            for (int j = m - 1; j >= 0; j--) {
                while (!st.empty() && mn[st.top()] >= mn[j])
                    st.pop();

                R[j] = st.empty() ? m : st.top();
                st.push(j);
            }

            for (int j = 0; j < m; j++) {
                ll total = pref[R[j]] - pref[L[j] + 1];
                ans = max(ans, total * mn[j]);
            }
        }
    }

    cout << ans << '\n';
}



// wewe f rsrw sdo w wer