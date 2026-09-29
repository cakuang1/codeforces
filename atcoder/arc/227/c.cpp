#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;
    cin >> N >> S;

    // KMP prefix function
    vector<int> pi(N);
    for (int i = 1; i < N; i++) {
        int j = pi[i - 1];
        while (j > 0 && S[i] != S[j]) j = pi[j - 1];
        if (S[i] == S[j]) j++;
        pi[i] = j;
    }

    // Shortest period length
    int p = N - pi[N - 1];
    if (N % p != 0) p = N;

    // Number of repeated copies of the period
    int K = N / p;

    // Repeat S N times
    string ops;
    ops.reserve(N * N);
    for (int i = 0; i < N; i++) {
        ops += S;
    }

    cout << K << '\n';
    cout << ops.size() << '\n';
    cout << ops << '\n';
}
// ww resp lew