#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string A, B, C;
    cin >> N >> A >> B >> C;

    vector<int> pa, pb, pc;

    for (int i = 0; i < 2 * N; i++) {
        if (A[i] == '1') pa.push_back(i);
        if (B[i] == '1') pb.push_back(i);
        if (C[i] == '1') pc.push_back(i);
    }

    string X(2 * N, '0');
    long long answer = 0;

    for (int k = 0; k < N; k++) {
        array<int, 3> p = {pa[k], pb[k], pc[k]};
        sort(p.begin(), p.end());

        int med = p[1];
        X[med] = '1';

        answer += abs(pa[k] - med);
        answer += abs(pb[k] - med);
        answer += abs(pc[k] - med);
    }

    cout << answer << '\n' << X << '\n';
}