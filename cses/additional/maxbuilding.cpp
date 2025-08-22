#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> forest(n);
    for (int i = 0; i < n; i++) {
        cin >> forest[i];
    }

    // Build height matrix
    vector<vector<int>> h(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++) {
        h[0][j] = (forest[0][j] == '.' ? 1 : 0);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            h[i][j] = (forest[i][j] == '.' ? h[i-1][j] + 1 : 0);
        }
    }

    // Helper: max rectangle in histogram H
    auto maxHistogram = [&](const vector<int>& H) {
        int M = H.size();
        stack<int> st;
        int best = 0;
        for (int j = 0; j <= M; j++) {
            int curH = (j < M ? H[j] : 0);
            while (!st.empty() && H[st.top()] >= curH) {
                int height = H[st.top()];
                st.pop();
                int left = st.empty() ? -1 : st.top();
                int width = j - left - 1;
                best = max(best, height * width);
            }
            st.push(j);
        }
        return best;
    };

    // Compute answer
    long long answer = 0;
    for (int i = 0; i < n; i++) {
        answer = max(answer, (long long) maxHistogram(h[i]));
    }

    cout << answer << "\n";
    return 0;
}


// how owuld youw esovle htis er