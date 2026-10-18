#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N, 0);
    vector<int> active;
    active.reserve(N);

    int answer = 0;

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int x;
            cin >> x;
            --x;

            if (A[x] == 0) {
                active.push_back(x);
            }

            answer ^= A[x];
            ++A[x];
            answer ^= A[x];
        } else {
            int remaining = 0;

            for (int x : active) {
                answer ^= A[x];
                --A[x];
                answer ^= A[x];

                if (A[x] > 0) {
                    active[remaining++] = x;
                }
            }

            active.resize(remaining);
        }

        cout << answer << '\n';
    }
}