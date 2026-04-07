#include <bits/stdc++.h>
using namespace std;

// odd-length Manacher on any string t
// p[i] = max k such that t[i-k+1 ... i+k-1] is palindrome
vector<int> manacher_odd(const string& t) {
    int n = t.size();
    vector<int> p(n);
    int l = 0, r = -1;

    for (int i = 0; i < n; i++) {
        int k = 1;
        if (i <= r) {
            int j = l + r - i;
            k = min(p[j], r - i + 1);
        }

        while (i - k >= 0 && i + k < n && t[i - k] == t[i + k]) {
            k++;
        }

        p[i] = k;

        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }

    return p;
}

// build # version and run one Manacher
vector<int> manacher_with_parity(const string& s) {
    string t;
    t.reserve(2 * (int)s.size() + 1);

    for (char c : s) {
        t += '#';
        t += c;
    }
    t += '#';

    return manacher_odd(t);
}

// werxcpl erisd w