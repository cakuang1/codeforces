#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, bool> memo;

// Helper function to check equivalency
bool areEquivalent(string a, string b) {
    // If already computed, return the result
    string key = a + "|" + b;
    if (memo.count(key)) {
        return memo[key];
    }

    // Base case: If strings are identical
    if (a == b) {
        return memo[key] = true;
    }

    // If lengths are not the same or odd, they cannot be split equivalently
    if (a.size() % 2 != 0 || b.size() % 2 != 0) {
        return memo[key] = false;
    }

    // Split strings into two halves
    int n = a.size() / 2;
    string a1 = a.substr(0, n), a2 = a.substr(n);
    string b1 = b.substr(0, n), b2 = b.substr(n);

    // Check both equivalency conditions recursively
    bool result = (areEquivalent(a1, b1) && areEquivalent(a2, b2)) ||
                  (areEquivalent(a1, b2) && areEquivalent(a2, b1));
    
    return memo[key] = result;
}


// cant we split  and when we do splti w
int main() {
    string a, b;
    cin >> a >> b;

    if (areEquivalent(a, b)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
