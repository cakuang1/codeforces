#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> cnt(6);
    for (int &x : cnt) cin >> x;

    int N;
    cin >> N;

    vector<int> coin = {1, 5, 10, 50, 100, 500};

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        for (int j = 5; j >= 0; j--) {
            int use = min(cnt[j], x / coin[j]);
            cnt[j] -= use;
            x -= use * coin[j];
        }

        if (x != 0) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
}