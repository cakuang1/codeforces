#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;

// Precompute factorials
vector<long long> factorial(int n) {
    vector<long long> fact(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    return fact;
}

// Compute the lexicographical rank of a permutation
long long getRank(const vector<int>& perm, const vector<long long>& fact) {
    int n = perm.size();
    long long rank = 0;
    vector<bool> used(n, false);

    for (int i = 0; i < n; i++) {
        int countSmaller = 0;
        for (int j = 0; j < perm[i]; j++) {
            if (!used[j]) countSmaller++;
        }
        rank += countSmaller * fact[n - i - 1];
        used[perm[i]] = true;
    }

    return rank;
}

// Convert a rank to a permutation
vector<int> getPermutation(long long rank, const vector<long long>& fact, int n) {
    vector<int> perm(n);
    vector<int> available(n);
    iota(available.begin(), available.end(), 0); // Fill with 0, 1, ..., n-1

    for (int i = 0; i < n; i++) {
        long long blockSize = fact[n - i - 1];
        int idx = rank / blockSize;
        rank %= blockSize;
        perm[i] = available[idx];
        available.erase(available.begin() + idx);
    }

    return perm;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> p(n), q(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> q[i];

    // Precompute factorials
    vector<long long> fact = factorial(n);

    // Compute ranks
    long long rankP = getRank(p, fact);
    long long rankQ = getRank(q, fact);

    // Compute resulting rank
    long long rankR = (rankP + rankQ) % fact[n];

    // Convert rank to permutation
    vector<int> result = getPermutation(rankR, fact, n);

    // Output the result
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}


// does this wmake wsense we a oedosetn ww w


// makehis dinner more intersting wm le  mole makes the ranking we   whow 