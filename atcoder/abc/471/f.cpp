#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string normalize(const string& s) {
    size_t pos = s.find_first_not_of('0');
    return pos == string::npos ? "0" : s.substr(pos);
}

string build(vector<string> a) {
    sort(a.begin(), a.end(), [](const string& x, const string& y) {
        return x + y > y + x;
    });

    string result;
    result.reserve(a.size() * 10);

    for (const string& s : a) {
        result += s;
    }

    return normalize(result);
}

// Compare integers represented without extra leading zeros.
bool larger(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() > b.size();
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<string> S(N);
    for (string& s : S) cin >> s;

    sort(S.begin(), S.end(), [](const string& a, const string& b) {
        if (a.size() != b.size()) return a.size() > b.size();
        return a > b;
    });
    
    
    // ws

    vector<string> candidate1(S.begin(), S.begin() + K);

    // Candidate 2: first K-1, plus maximum numeric value
    // among all remaining strings.
    int best = K - 1;
    ll bestValue = stoll(S[best]);

    for (int i = K; i < N; ++i) {
        ll value = stoll(S[i]);
        if (value > bestValue) {
            bestValue = value;
            best = i;
        }
    }

    vector<string> candidate2(S.begin(), S.begin() + K - 1);
    candidate2.push_back(S[best]);

    string ans1 = build(candidate1);
    string ans2 = build(candidate2);

    cout << (larger(ans1, ans2) ? ans1 : ans2) << '\n';
}
