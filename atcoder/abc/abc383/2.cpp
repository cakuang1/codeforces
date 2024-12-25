#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing

// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);

// Function to compute x^y % mod using binary exponentiation
ll modExp(ll x, ll y, ll m = mod) {
    ll res = 1;
    x = x % m;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % m;
        }
        y = y >> 1;
        x = (x * x) % m;
    }
    return res;
}

// wwho wes writ hsi w

struct StringHash {
    vector<ll> hash, power;
    ll n;

    StringHash(const string &s) {
        n = s.size();
        hash.resize(n + 1, 0);
        power.resize(n + 1, 1);

        // Precompute hash values and powers of p
        for (int i = 0; i < n; i++) {
            hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * power[i]) % mod;
            if (i < n - 1)
                power[i + 1] = (power[i] * p) % mod;
        }
    }

    // Compute hash of substring s[l..r] (0-based indexing)
    ll getHash(int l, int r) {
        ll result = (hash[r + 1] - hash[l] * power[r - l + 1] % mod + mod) % mod;
        return result;
    }
};

// Function to compute modular inverse of a under modulo mod
ll modInverse(ll a, ll m = mod) {
    return modExp(a, m - 2, m); // Fermat's Little Theorem for prime mod
}

// Function to precompute factorials and their modular inverses
void precomputeFactorials(int n, ll m = mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % m;
    }
    invFact[n] = modExp(fact[n], m - 2, m); // Fermat's Little Theorem for modular inverse
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % m;
    }
}

// Function to calculate nCr % mod
ll nCr(int n, int r, ll m = mod) {
    if (r > n || r < 0) return 0;
    return (((fact[n] * invFact[r]) % m) * invFact[n - r]) % m;
}

// Function to calculate nPr % mod
ll nPr(int n, int r, ll m = mod) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[n - r]) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, t;
    cin >> n >> m >> t;

    vector<pair<int, int>> floors;
    vector<vector<char>> grid(n, vector<char>(m));
    
    // Corrected grid reading loop
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { // Changed i < m to j < m
            cin >> grid[i][j];
            if (grid[i][j] == '.') {
                floors.emplace_back(i, j);
            }
        }
    }

    vector<pair<int, int>> dir = { {1,0}, {0,1}, {-1,0}, {0,-1} };
    int res = 0;

    int k = floors.size();
    // Iterate over all unique pairs of floor cells
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) { // Changed i++ to j++
            // Set to keep track of seen cells
            set<pair<int, int>> seen;

            // Initialize BFS
            int dist = 0;
            queue<pair<int, int>> q;
            q.push(floors[i]);
            seen.emplace(floors[i]);
            q.push(floors[j]);
            seen.emplace(floors[j]);
            int count = 2; 
            while (!q.empty() && dist < t) {
                int length = q.size();
                for (int p = 0; p < length; p++) { // Renamed loop variable to avoid conflict
                    auto current = q.front();
                    q.pop();
                    for (auto &d : dir) {
                        int ni = current.first + d.first;
                        int nj = current.second + d.second;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == '.') {
                            pair<int, int> neighbor = {ni, nj};
                            if (seen.find(neighbor) == seen.end()) {
                                seen.emplace(neighbor);
                                if (grid[neighbor.first][neighbor.second] == '.'){
                                    count ++; 
                                }
                                q.push(neighbor);
                        }
                    }
                }
                if (dist == t) {
                    break;
                }
                dist++;

            }
            res = max(res, (int)seen.size());
        }
    }
    }

    cout << res << endl;

    return 0;
}
