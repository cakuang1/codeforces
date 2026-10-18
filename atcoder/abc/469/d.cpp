#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> tournaments(M);
    for (auto& [a, b] : tournaments) {
        cin >> a >> b;
    }

    auto countPartners = [&](int x) -> ll {
        vector<int> candidates;
        bool initialized = false;

        for (auto [a, b] : tournaments) {
            if (a == x || b == x) continue;

            if (!initialized) {
                candidates = {a, b};
                initialized = true;
            } else {
                vector<int> remaining;

                for (int y : candidates) {
                    if (y == a || y == b) {
                        remaining.push_back(y);
                    }
                }

                candidates = remaining;
            }

            if (candidates.empty()) return 0;
        }

        // Every tournament already contains x.
        if (!initialized) return N - 1;

        return candidates.size();
    };


    /// erw na irp ossoslsrsi ein ew wer
    

    auto [a, b] = tournaments[0];

    ll answer = countPartners(a) + countPartners(b);

    // Pair (a, b) was counted twice if it is valid.
    bool valid = true;

    for (auto [u, v] : tournaments) {
        if (u != a && v != a && u != b && v != b) {
            valid = false;
            break;
        }
    }
    
    if (valid) --answer;

    cout << answer << '\n';
    return 0;
}
// w siww wssjra insi a sisn aaslso nri w

// wdfwerd wern wrs ars wrw w

/ ew ewrf ewsdf ewswsesps weri wr