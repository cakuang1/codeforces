#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> cnt(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<int> B;
    vector<int> st;
    B.reserve(N);
    st.reserve(N);

    for (int L = 0; L < N; L++) {
        if (cnt[L] > 0) {
            // First occurrence of L goes here.
            B.push_back(L);
            cnt[L]--;

            // Other copies of L must appear later.
            while (cnt[L] > 0) {
                st.push_back(L);
                cnt[L]--;
            }
        } else if (!st.empty()) {
            B.push_back(st.back());
            st.pop_back();
        } else {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
    for (int i = 0; i < N; i++) {
        cout << B[i] << (i + 1 == N ? '\n' : ' ');
    }
}

//