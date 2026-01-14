#include <bits/stdc++.h>
using namespace std;


//w edvl seorps dso smrsetn se
 int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    long long X;
    cin >> N >> K >> X;

    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    vector<string> all;

    all.reserve((int)pow(N, K)); // small; just a hint

    string cur;
    function<void(int)> dfs = [&](int depth) {
        if (depth == K) {
            all.push_back(cur);
            return;
        }
        for (int i = 0; i < N; i++) {
            int old_len = (int)cur.size();
            cur += S[i];
            dfs(depth + 1);
            cur.resize(old_len);
        }
    };

    dfs(0);

    sort(all.begin(), all.end());
    cout << all[(int)(X - 1)] << "\n";
    return 0;
}

