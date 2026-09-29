#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, int>> events;
    events.reserve(2 * N);

    for (int i = 0; i < N; i++) {
        int S, T;
        cin >> S >> T;

        events.push_back({S, +1}); // meeting starts
        events.push_back({T, -1}); // meeting ends
    }

    sort(events.begin(), events.end());

    int active = 0;
    int components = 0;

    for (auto [time, type] : events) {
        if (type == +1) {
            if (active == 0) {
                components++;
            }

            active++;

            if (active >= 3) {
                cout << 0 << '\n';
                return 0;
            }
        } else {
            active--;
        }
    }

    long long answer = 1;
    for (int i = 0; i < components; i++) {
        answer = answer * 2 % MOD;
    }

    cout << answer << '\n';
}



// wer dof wfsd weirs wer
/ 