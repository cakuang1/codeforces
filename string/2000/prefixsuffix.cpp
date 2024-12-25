#include <bits/stdc++.h>
using namespace std;

// Function to compute the prefix function
vector<int> computePrefixFunction(const string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Step 1: Compute the prefix function
    vector<int> pi = computePrefixFunction(s);

    // Step 2: Determine all prefix lengths that are also suffixes
    vector<int> matchingLengths;
    int k = pi[n - 1];
    while (k > 0) {
        matchingLengths.push_back(k);
        k = pi[k - 1];
    }
    reverse(matchingLengths.begin(), matchingLengths.end());

    // Include the full string itself as a prefix-suffix match
    matchingLengths.push_back(n);

    // Step 3: Count occurrences of each prefix length in the string
    vector<int> count(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        count[pi[i]]++;
    }

    // Accumulate counts
    for (int i = n - 1; i > 0; --i) {
        count[pi[i - 1]] += count[i];
    }

    // Each prefix itself also appears once
    for (int i = 0; i <= n; ++i) {
        count[i]++;
    }

    // Step 4: Output results
    cout << matchingLengths.size() << endl;
    for (int length : matchingLengths) {
        cout << length << " " << count[length] << endl;
    }

    return 0;
}
