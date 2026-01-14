#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int M = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M = max(M, a[i]);
    }

    // count[v] = how many times v appears (capped at 2)
    vector<int> count(M+1, 0);
    // pos[v][0..1] = first two positions where value v appears
    vector<array<int,2>> pos(M+1, array<int,2>{-1,-1});

    for (int i = 0; i < n; i++) {
        int v = a[i];
        if (count[v] < 2) {
            pos[v][count[v]] = i;
        }
        count[v]++;
    }

    ll bestLCM = LLONG_MAX;
    int ans_i = 0, ans_j = 1;

    // For each possible divisor d
    for (int d = 1; d <= M; d++) {
        int first = -1, second = -1;

        // scan multiples of d
        for (int k = d; k <= M; k += d) {
            if (count[k] == 0) continue;
            if (count[k] > 1) {
                // we have at least two occurrences of k itself
                first = second = k;
                break;
            }
            if (first == -1) {
                first = k;
            } else {
                second = k;
                break;
            }
        }

        if (second == -1) continue; // fewer than two multiples

        // compute candidate LCM = (first * second) / d
        ll cand = (ll)first * (ll)second / d;
        if (cand < bestLCM) {
            bestLCM = cand;
            if (first == second) {
                // two distinct positions storing the same value
                ans_i = pos[first][0];
                ans_j = pos[first][1];
            } else {
                ans_i = pos[first][0];
                ans_j = pos[second][0];
            }
        }
    }

    // output 1-based indices in increasing order
    if (ans_i > ans_j) swap(ans_i, ans_j);
    cout << ans_i+1 << " " << ans_j+1 << "\n";
    return 0;
}

// atleats wer