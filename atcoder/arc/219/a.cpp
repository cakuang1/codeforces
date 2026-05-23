#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    unordered_set<string> forbidden;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;

        // T cannot be the complement of s
        for ( char &c : s ) {
            c = (c == '0' ? '1' : '0');
        }

        forbidden.insert(s);
    }

    // If M is small enough and all 2^M strings are forbidden, impossible.
    if (M <= 20 && N == (1 << M)) {
        cout << "No\n";
        return 0;
    }

    // Try N+1 candidate strings: 000..., 000...1, ...
    for (int x = 0; x <= N; x++) {
        string t(M, '0');

        int y = x;
        for (int j = M - 1; j >= 0 && y > 0; j--) {
            t[j] = char('0' + (y & 1));
            y >>= 1;
        }

        if (!forbidden.count(t)) {
            cout << "Yes\n";
            cout << t << '\n';
            return 0;
        }
    }

    cout << "No\n";
    return 0;
}


// we s Rewvsr srosiamtion wr
// w

// persmasshiss ssxcaltww osncwe



//