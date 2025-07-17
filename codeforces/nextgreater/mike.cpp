#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> L(n), R(n);
    vector<int> st;

    // 1) Find for each i the leftmost index where arr[j] < arr[i]
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.back()] >= arr[i])
            st.pop_back();
        L[i] = st.empty() ? 0 : st.back() + 1;
        st.push_back(i);
    }
    // 2) Clear stack and do the same from the right
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.back()] > arr[i])
            st.pop_back();
        R[i] = st.empty() ? n - 1 : st.back() - 1;
        st.push_back(i);
    }
    // 3) For each i, arr[i] is the minimum of exactly
    //    len = R[i] - L[i] + 1 window size subarrays ending at i,
    //    so we record the maximum-minimum for each length:
    vector<int> res(n, INT_MIN);
    for (int i = 0; i < n; i++) {
        int len = R[i] - L[i] + 1;
        res[len - 1] = max(res[len - 1], arr[i]);
    }

    // 4) Some lengths may be empty; fill them by propagating
    //    the maximum to the left (suffix max):
    for (int i = n - 2; i >= 0; i--) {
        res[i] = max(res[i], res[i + 1]);
    }
    

    // 5) Output:
    for (int i = 0; i < n; i++) {
        cout << res[i] << (i + 1 < n ? ' ' : '\n');
    }

    return 0;
}

