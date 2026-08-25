#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

vector<int> findSubset(int N, ull K, const vector<ull>& A) {
    // Each basis element:
    //   value = XOR value
    //   mask  = which original A[i]'s produce it
    vector<pair<ull, ull>> basis;

    // Zero-XOR subsets (nullspace vectors).
    // 0 itself is also allowed.
    vector<ull> nullspace = {0};

    auto reduce = [&](ull v) {
        ull mask = 0;

        for (auto [x, m] : basis) {
            if ((v ^ x) < v) {
                v ^= x;
                mask ^= m;
            }
        }

        return pair<ull, ull>{v, mask};
    };

    // Build XOR basis while remembering representations.
    for (int i = 0; i < N; i++) {
        auto [v, mask] = reduce(A[i]);

        if (v != 0) {
            basis.push_back({
                v,
                mask ^ (1ULL << i)
            });
        } else {
            // A[i] XOR "mask" = 0
            nullspace.push_back(
                mask ^ (1ULL << i)
            );
        }
    }

    // Find one subset whose XOR is K.
    auto [v, baseMask] = reduce(K);

    if (v != 0) {
        return {};
    }

    // The two forbidden alternating subsets.
    ull bad0 = 0;
    ull bad1 = 0;

    for (int i = 0; i < N; i++) {
        if (i % 2 == 0)
            bad0 |= (1ULL << i);
        else
            bad1 |= (1ULL << i);
    }

    // baseMask XOR any zero-XOR subset is still a solution.
    for (ull z : nullspace) {
        ull mask = baseMask ^ z;

        if (mask != bad0 && mask != bad1) {
            vector<int> S(N);

            for (int i = 0; i < N; i++) {
                S[i] = (mask >> i) & 1ULL;
            }

            return S;
        }
    }

    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        ull K;

        cin >> N >> K;

        vector<ull> A(N);
        for (auto& x : A) cin >> x;

        vector<int> S = findSubset(N, K, A);

        if (S.empty()) {
            cout << "No\n";
            continue;
        }

        /*
            S[i] = 1 means original A[i] should contribute
            to the XOR that eventually reaches position 0.

            Since S is not alternating, there exists adjacent
            positions p,p+1 with S[p] == S[p+1].
        */

        int p = -1;

        for (int i = N - 2; i >= 0; i--) {
            if (S[i] == S[i + 1]) {
                p = i;
            }
        }

        vector<int> ops;

        /*
            First create a pair of zeros around p,p+1.
        */

        if (S[p] == 0 && S[p + 1] == 0) {
            // Applying same operation twice:
            //
            // (a,b) -> (a^b,a^b) -> (0,0)
            ops.push_back(p);
            ops.push_back(p);
        } else {
            // S[p] = S[p+1] = 1.
            //
            // Convert this situation into a nearby 00 case.
            if (p != N - 2) {
                if (S[p + 2] == 1) {
                    ops.push_back(p);
                    ops.push_back(p + 1);
                    ops.push_back(p);
                    ops.push_back(p);
                } else {
                    ops.push_back(p);
                    ops.push_back(p + 1);
                    ops.push_back(p + 1);
                    p++;
                }
            } else {
                ops.push_back(p);
                ops.push_back(p - 1);
                ops.push_back(p - 1);
                p--;
            }
        }

        /*
            Collect selected elements on the LEFT into position p+1.
        */

        for (int i = p - 1; i >= 0; i--) {
            if (S[i]) {
                for (int j = i + 1; j < p; j++) {
                    ops.push_back(j);
                    ops.push_back(j);
                    ops.push_back(j - 1);
                }

                ops.push_back(p - 1);
                ops.push_back(p);
            }
        }

        /*
            Move the accumulated XOR from around p to position 0.
        */

        for (int i = p - 1; i >= 0; i--) {
            ops.push_back(i);
            ops.push_back(i);
            ops.push_back(i + 1);
            ops.push_back(i);
        }

        /*
            Collect selected elements on the RIGHT into position 0.
        */

        for (int i = p + 2; i < N; i++) {
            if (S[i]) {
                for (int j = i - 2; j > 0; j--) {
                    ops.push_back(j);
                    ops.push_back(j);
                    ops.push_back(j + 1);
                }

                ops.push_back(1);
                ops.push_back(0);
            }
        }

        cout << "Yes\n";
        cout << ops.size() << '\n';

        for (int i = 0; i < (int)ops.size(); i++) {
            if (i) cout << ' ';
            cout << ops[i] + 1;
        }
        cout << '\n';
    }

    return 0;
}

// werais msoc wle ewl psodinow r

/ w