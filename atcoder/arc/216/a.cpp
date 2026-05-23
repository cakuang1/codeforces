#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        string A, B;
        cin >> N >> A >> B;

        if (A[0] != B[0]) {
            cout << -1 << '\n';
            continue;
        }

        auto transform = [&](const string& s) {
            string u;
            for (int i = 0; i + 1 < N; i++) {
                int t = (s[i] != s[i + 1]);

                // flip even positions in 1-indexing
                if (i % 2 == 1) t ^= 1;

                u.push_back(char('0' + t));
            }
            return u;
        };

        string X = transform(A);
        string Y = transform(B);

        vector<int> px, py;

        for (int i = 0; i < N - 1; i++) {
            if (X[i] == '0') px.push_back(i);
            if (Y[i] == '0') py.push_back(i);
        }

        if (px.size() != py.size()) {
            cout << -1 << '\n';
            continue;
        }

        long long ans = 0;
        for (int i = 0; i < (int)px.size(); i++) {
            ans += abs(px[i] - py[i]);
        }

        cout << ans << '\n';
    }

    return 0;
}

// w scm wrs wer
// w whsdf whrwm wer
// wage ew
