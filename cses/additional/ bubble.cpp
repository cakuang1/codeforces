#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Pair each value with its original index
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = make_pair(a[i], i);
    }

    // Stable sort by value (preserves relative order of equal elements)
    stable_sort(v.begin(), v.end(),
        [](const pair<int,int>& L, const pair<int,int>& R) {
            return L.first < R.first;
        }
    );

    // Compute the maximum distance any element has to move left
    int rounds = 0;
    for (int new_i = 0; new_i < n; new_i++) {
        int orig_i = v[new_i].second;
        int dist = orig_i - new_i;
        if (dist > rounds) {
            rounds = dist;
        }
    }

    // This is the number of bubble‐sort passes with at least one swap
    cout << rounds << "\n";
    return 0;
}


/