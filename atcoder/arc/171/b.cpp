#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N + 1);
    vector<int> first(N + 1, -1);
    vector<int> last(N + 1, -1);

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];

        if (first[A[i]] == -1) {
            first[A[i]] = i;
        }
        last[A[i]] = i;
    }

    vector<bool> isStart(N + 1, false);
    vector<bool> isEndpoint(N + 1, false);

    for (int v = 1; v <= N; ++v) {
        if (first[v] == -1) {
            continue;
        }

        // The increasing path for value v must end at vertex v.
        if (last[v] != v) {
            cout << 0 << '\n';
            return 0;
        }

        isStart[first[v]] = true;
        isEndpoint[v] = true;
    }

    long long answer = 1;
    long long availableStarts = 0;

    for (int x = 1; x <= N; ++x) {
        if (isStart[x]) {
            ++availableStarts;
        }

        if (isEndpoint[x]) {
            if (availableStarts == 0) {
                cout << 0 << '\n';
                return 0;
            }

            answer = answer * availableStarts % MOD;
            --availableStarts;
        }
    }

    cout << answer << '\n';
}