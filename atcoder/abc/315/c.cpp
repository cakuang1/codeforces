
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> D(M);
    int total = 0;

    for (int &x : D) {
        cin >> x;
        total += x;
    }

    int mid = (total + 1) / 2;
    int prefix = 0;

    for (int i = 0; i < M; i++) {
        if (prefix + D[i] >= mid) {
            cout << i + 1 << " " << mid - prefix << '\n';
            break;
        }
        prefix += D[i];
    }
}
