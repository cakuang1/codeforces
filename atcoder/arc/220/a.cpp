#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        if (N == 2 || N == 3 || N == 5) {
            cout << "No\n";
            continue;
        }

        deque<int> a;

        if (N % 3 == 1) {
            // length 1
            a = {1};
        }
        else if (N % 3 == 0) {
            // length 6
            // 3/4 + 2/9 + 1/36 = 1
            a = {2, 2, 2, 3, 3, 6};
        }
        else {
            // length 8
            // 2/4 + 4/9 + 2/36 = 1
            a = {2, 2, 3, 3, 3, 3, 6, 6};
        }

        // Each operation:
        //
        // x -> 2x, 2x, 2x, 2x
        //
        // length increases by 3
        while ((int)a.size() < N) {
            int x = a.front();
            a.pop_front();

            for (int i = 0; i < 4; i++) {
                a.push_back(2 * x);
            }
        }

        cout << "Yes\n";

        for (int i = 0; i < N; i++) {
            cout << a[i] << (i + 1 == N ? '\n' : ' ');
        }
    }

    return 0;
}

