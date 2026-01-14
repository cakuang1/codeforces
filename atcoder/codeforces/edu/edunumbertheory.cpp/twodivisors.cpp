#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 2;
vector<int> minDiv(MAXN);

// Function to precompute the smallest prime factor (SPF) for each number
void preprocess() {
    iota(minDiv.begin(), minDiv.end(), 0); // Initialize minDiv[i] = i

    for (int i = 2; i * i < MAXN; i++) {
        if (minDiv[i] == i) { // `i` is prime
            for (int j = i; j < MAXN; j += i) {
                minDiv[j] = min(minDiv[j], i);
            }
        }
    }
}

// Function to get distinct prime divisors of a number
vector<int> getPrimeDivisors(int v) {
    vector<int> ans;
    while (v > 1) {
        if (ans.empty() || ans.back() != minDiv[v]) {
            ans.push_back(minDiv[v]);
        }
        v /= minDiv[v];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preprocess(); // Compute the smallest prime factor for numbers up to MAXN

    int n;
    cin >> n;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> d1(n, -1), d2(n, -1);
    
    for (int i = 0; i < n; i++) {
        vector<int> factors = getPrimeDivisors(a[i]);

        if (factors.size() >= 2) {
            d1[i] = factors[0];
            d2[i] = 1;
            for (int j = 1; j < factors.size(); j++) {
                d2[i] *= factors[j];
            }
        }
    }

    // Print the results
    for (int i = 0; i < n; i++) cout << d1[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << d2[i] << " ";
    cout << "\n";

    return 0;
}
