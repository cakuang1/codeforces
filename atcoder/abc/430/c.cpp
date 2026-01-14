#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, A, B;
    cin >> N >> A >> B;
    string S;
    cin >> S;

    // prefix counts
    vector<int> preA(N+1), preB(N+1);
    for (int i = 0; i < N; i++) {
        preA[i+1] = preA[i] + (S[i]=='a');
        preB[i+1] = preB[i] + (S[i]=='b');
    }

    auto countA = [&](int l, int r){ return preA[r+1]-preA[l]; };
    auto countB = [&](int l, int r){ return preB[r+1]-preB[l]; };

    long long ans = 0;

    int al = 0, bl = 0;

    for (int l = 0; l < N; l++) {

        // Move al until A a's
        while (al < N && countA(l, al) < A) al++;
        if (al == N) break; // no more possible

        // Move bl while < B b's
        while (bl < N && countB(l, bl) < B) bl++;

        int rmin = al;
        int rmax = bl - 1;

        if (rmin <= rmax) ans += (long long)(rmax - rmin + 1);
    }

    cout << ans << "\n";
}
// wfdi nwethwe wer we