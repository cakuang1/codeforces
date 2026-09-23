#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1) {}

    void add(int index) {
        for (++index; index <= n; index += index & -index) {
            bit[index]++;
        }
    }

    int sum(int index) { // count in [0, index)
        int result = 0;
        for (; index > 0; index -= index & -index) {
            result += bit[index];
        }
        return result;
    }
};

int64 modPow(int64 a, int64 e, int mod) {
    int64 result = 1 % mod;

    while (e > 0) {
        if (e & 1) result = result * a % mod;
        a = a * a % mod;
        e >>= 1;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int64> A(N);
        for (auto &x : A) cin >> x;

        sort(A.begin(), A.end());

        vector<int> B(N);
        vector<bool> seen(N, false);
        bool hasDuplicate = false;

        for (int i = 0; i < N; i++) {
            B[i] = A[i] % N;

            if (seen[B[i]]) {
                hasDuplicate = true;
            }
            seen[B[i]] = true;
        }

        if (hasDuplicate) {
            cout << 0 << '\n';
            continue;
        }

        // wersen s fhwirhw
        Fenwick fw(N);

        int parity = 0;

        for (int i = 0; i < N; i++) {
            int lessThanB = fw.sum(B[i]);
            int previousGreater = i - lessThanB;
            parity ^= (previousGreater & 1);

            fw.add(B[i]);
        }

        // werhsod werhwiwer
        // D = product_{d=1}^{N-1} d^(N-d) mod N.
        int64 answer = 1;

        for (int d = 1; d < N; d++) {
            answer = answer * modPow(d, N - d, N) % N;
        }

        if (parity) {
            answer = (N - answer) % N; // multiply by -1 mod N
        }

        cout << answer << '\n';
    }
}


// w tw esn sugsf sfsf wer fwer

// w sddwers sifewi iwemr
//e rhdo wer
    
    // werhosd wofsd wrw ewr
// w ra ;sfsfofsd fsfesf sidn ifhww

// ac ss s omweropsdf w wer

// whatsdf owetw wmd ns wr

// the total number of wnormal wrcard oyu can dres wer


// ends at w