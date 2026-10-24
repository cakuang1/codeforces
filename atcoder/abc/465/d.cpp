#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll X, Y, K;
        cin >> X >> Y >> K;

        int answer = 0;

        while (X != Y) {
            if (X > Y) {
                X /= K;
            } else {
                Y /= K;
            }
            ++answer;
        }

        cout << answer << '\n';
    }
} 