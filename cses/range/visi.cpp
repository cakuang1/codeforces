#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> h(n);
    for(int i = 0; i < n; i++){
        cin >> h[i];
    }

    // 1) Next‑greater element to the right, sentinel at index n
    vector<int> nextG(n+1, n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && h[st.top()] < h[i]){
            nextG[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    // nextG[n] stays n

    // 2) Build binary–lifting table up[d][i] = 2^d‑th nextG‑jump from i
    int MAXLOG = __lg(n) + 2;
    vector<vector<int>> up(MAXLOG, vector<int>(n+1));
    // level 0 = 1‑step jumps
    for(int i = 0; i <= n; i++){
        up[0][i] = nextG[i];
    }
    // build higher levels
    for(int d = 1; d < MAXLOG; d++){
        for(int i = 0; i <= n; i++){
            up[d][i] = up[d-1][ up[d-1][i] ];
        }
    }

    // 3) Answer queries
    // For each [a,b], we start at L=a-1, count how many next‑greater jumps stay ≤ R=b-1
    while(q--){
        int a, b;
        cin >> a >> b;
        int L = a - 1;
        int R = b - 1;

        int cnt = 1;      // we always see building at L itself
        int cur = L;
        // try to jump as far as possible in powers of two
        for(int d = MAXLOG - 1; d >= 0; d--){
            int nx = up[d][cur];
            if (nx <= R){
                cnt += 1 << d;
                cur = nx;
            }
        }
        cout << cnt << "\n";
    }

    return 0;
}

