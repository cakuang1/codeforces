#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> L(n), R(n), Lp(n), Rp(n);
    stack<int> st;

    // Compute L[i]: count of strictly smaller to the left for max
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i])
            st.pop();
        L[i] = st.empty() ? i : i - st.top() - 1;
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // Compute R[i]: count of <= to the right for max
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] <= a[i])
            st.pop();
        R[i] = st.empty() ? (n - 1 - i) : (st.top() - i - 1);
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // Compute Lp[i]: count of strictly greater to the left for min
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] > a[i])
            st.pop();
        Lp[i] = st.empty() ? i : i - st.top() - 1;
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // Compute Rp[i]: count of >= to the right for min
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] >= a[i])
            st.pop();
        Rp[i] = st.empty() ? (n - 1 - i) : (st.top() - i - 1);
        st.push(i);
    }

    ll Smax = 0, Smin = 0;
    for (int i = 0; i < n; i++) {
        Smax += (ll)a[i] * (L[i] + 1) * (R[i] + 1);
        Smin += (ll)a[i] * (Lp[i] + 1) * (Rp[i] + 1);
    }
    cout << (Smax - Smin) << "\n";
    return 0;
}

