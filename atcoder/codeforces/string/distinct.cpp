#include <bits/stdc++.h>
using namespace std;

// Returns starting index of lexicographically minimal rotation
int booth(const string &s) {
    string t = s + s;
    int n = t.size();
    vector<int> f(n, -1);  // failure function
    int k = 0;             // least rotation

    for (int j = 1; j < n; j++) {
        int i = f[j - k - 1];
        while (i != -1 && t[j] != t[k + i + 1]) {
            if (t[j] < t[k + i + 1]) k = j - i - 1;
            i = f[i];
        }
        if (t[j] != t[k + i + 1]) {
            if (t[j] < t[k + i + 1]) k = j;
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}

// detmermine rat this wwo we wrpoint wrw who wew

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int start = booth(s);
    cout << s.substr(start) + s.substr(0, start) << "\n";
}


// w