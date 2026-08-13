#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long N, A, B;
        cin >> N >> A >> B;

        if (A > N) {
            cout << "No\n";
            continue;
        }

        long long remaining = N - A;
        long long maxPawns =
            remaining * ((remaining + 1) / 2);

        cout << (B <= maxPawns ? "Yes\n" : "No\n");
    }
}