#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    // room[i] = 0 -> X
    // room[i] = 1 -> Y
    vector<int> room(N, 0);

    while (true) {
        bool moved = false;

        for (int i = 0; i < N; i++) {
            int same = 0;
            int other = 0;

            for (int j = 0; j < N; j++) {
                if (i == j) continue;

                if (room[i] == room[j])
                    same += A[i][j];
                else
                    other += A[i][j];
            }

            // Person i is not in a good state.
            if (same < other) {
                room[i] ^= 1;
                moved = true;
                break;
            }
        }

        if (!moved) break;
    }

    for (int i = 0; i < N; i++) {
        cout << (room[i] == 0 ? 'X' : 'Y');
    }
    cout << '\n';

    return 0;
}

// we