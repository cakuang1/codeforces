#include <bits/stdc++.h>
using namespace std;

// CSES – Advertisement
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> h(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    // Sentinel bar
    h[n] = 0;

    stack<int> st;
    long long max_area = 0;

    for (int i = 0; i <= n; i++) {
        // While the current height is less than the height at stack top:
        while (!st.empty() && h[i] < h[st.top()]) {
            int height_idx = st.top();
            st.pop();
            long long height = h[height_idx];
            // If stack is empty, width spans from 0 to i−1 => i
            long long width = st.empty() 
                              ? i 
                              : (i - st.top() - 1);
            max_area = max(max_area, height * width);
        }
        st.push(i);
    }

    cout << max_area << "\n";
    return 0;
}


// the w