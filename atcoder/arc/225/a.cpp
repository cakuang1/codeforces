#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // X color:  1  2  3  4
    // Y color:  2  4  1  3
    int mp[5] = {0, 2, 4, 1, 3};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x;
            cin >> x;
            cout << mp[x] << (j + 1 == N ? '\n' : ' ');
        }
    }
}