#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18; // Large value for long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    // Coordinate compression: get sorted unique values
    vector<int> b = a;
    sort(b.begin(), b.end());

    // DP arrays: use only two 1D arrays
    vector<long long> prev(N, INF), curr(N, INF);

    // Base case: first element
    for (int j = 0; j < N; j++) {
        prev[j] = abs(a[0] - b[j]);
    }

    // Fill DP table using 1D arrays
    for (int i = 1; i < N; i++) { // For each element in a
        long long minsofar = INF;
        for (int j = 0; j < N; j++) { // For each possible value in b
            minsofar = min(minsofar, prev[j]);
            curr[j] = minsofar + abs(a[i] - b[j]);
        }
        swap(prev, curr); // Move to the next row
    }


    // why does this work  
    // Find the result from the last row
    long long result = *min_element(prev.begin(), prev.end());
    cout << result << endl;

    return 0;
}
